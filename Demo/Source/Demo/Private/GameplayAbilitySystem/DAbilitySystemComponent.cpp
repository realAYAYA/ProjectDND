﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystemLog.h"
#include "DProjectile.h"
#include "Abilities/DGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Net/UnrealNetwork.h"

void UDAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	TurnBasedActiveGameplayEffectsContainer.RegisterWithOwner(this);
	TurnBasedActiveGameplayEffectsContainer.SetIsUsingReplicationCondition(true);

	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::NotifyGameplayEffectAppliedToBP);
	ActiveGameplayEffects.OnActiveGameplayEffectRemovedDelegate.AddUObject(this, &UDAbilitySystemComponent::NotifyGameplayEffectRemovedToBP);
}

FGameplayAbilitySpecHandle UDAbilitySystemComponent::FindAbilityWithTag(const FGameplayTag& Tag) const
{
	const FGameplayTagContainer Container(Tag);
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	FindAllAbilitiesWithTags(AbilitySpecHandles, Container);
	if (AbilitySpecHandles.Num() == 0)
		return FGameplayAbilitySpecHandle();
	
	const auto AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandles[0]);
	const auto AbilityInstance = AbilitySpec->GetPrimaryInstance();
	if (!AbilityInstance)
		return FGameplayAbilitySpecHandle();

	// 技能唯一才合法，存在多个技能实例则不适用该方法
	if (AbilityInstance->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::InstancedPerActor)
		return FGameplayAbilitySpecHandle();

	return AbilitySpecHandles[0];
}

bool UDAbilitySystemComponent::ConfirmTargetDataWithTag(const FGameplayTag& Tag, const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	const FGameplayAbilitySpecHandle AbilitySpecHandle = FindAbilityWithTag(Tag);
	if (!AbilitySpecHandle.IsValid())
		return false;
	
	const auto AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandle);
	const auto AbilityInstance = AbilitySpec->GetPrimaryInstance();
	if (!AbilityInstance)
		return false;

	CallServerSetReplicatedTargetData(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), TargetDataHandle, Tag, ScopedPredictionKey);
	return true;
}

void UDAbilitySystemComponent::CancelTargetDataWithTag(const FGameplayTag& Tag)
{
	const FGameplayAbilitySpecHandle AbilitySpecHandle = FindAbilityWithTag(Tag);
	if (!AbilitySpecHandle.IsValid())
		return;
	
	const auto AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandle);
	const auto AbilityInstance = AbilitySpec->GetPrimaryInstance();
	if (!AbilityInstance)
		return;

	ServerSetReplicatedTargetDataCancelled(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), ScopedPredictionKey);
}

void UDAbilitySystemComponent::CheckTurnDurationExpired()
{
	TurnBasedActiveGameplayEffectsContainer.CheckTurnDuration();
}

void UDAbilitySystemComponent::ExecuteTurnBasedPeriodicEffect(const FActiveGameplayEffectHandle& Handle)
{
	ActiveGameplayEffects.ExecutePeriodicGameplayEffect(Handle);
}

int32 UDAbilitySystemComponent::GetActiveEffectRemainingTurn(const FActiveGameplayEffectHandle& ActiveHandle) const
{
	return TurnBasedActiveGameplayEffectsContainer.GetActiveEffectRemainingTurn(ActiveHandle);
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::K2_ApplyTurnBasedGameplayEffectToSelf(
	const TSubclassOf<UDGameplayEffect>& GameplayEffectClass, const int32 Level, const int32 CustomDuration, FGameplayEffectContextHandle EffectContext)
{
	if ( GameplayEffectClass )
	{
		if (!EffectContext.IsValid())
		{
			EffectContext = MakeEffectContext();
			EffectContext.AddInstigator(this->GetOwner(), this->GetOwner());
			EffectContext.AddActors({this->GetOwner()});
			EffectContext.AddSourceObject(this);
		}
		
		const UDGameplayEffect* GameplayEffect = GameplayEffectClass->GetDefaultObject<UDGameplayEffect>();
		return ApplyTurnBasedGameplayEffectToSelf(GameplayEffect, Level, CustomDuration, EffectContext);
	}

	return FActiveGameplayEffectHandle();
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectToSelf(
	const UGameplayEffect* GameplayEffect,
	const int32 Level,
	const int32 CustomDuration,
	const FGameplayEffectContextHandle& EffectContext,
	const FPredictionKey& PredictionKey)
{
	if (GameplayEffect == nullptr)
	{
		ABILITY_LOG(Error, TEXT("UAbilitySystemComponent::ApplyGameplayEffectToSelf called by Instigator %s with a null GameplayEffect."), *EffectContext.ToString());
		return FActiveGameplayEffectHandle();
	}

	if (GameplayEffect->DurationPolicy == EGameplayEffectDurationType::HasDuration)
		return FActiveGameplayEffectHandle();

	if (HasNetworkAuthorityToApplyGameplayEffect(PredictionKey))
	{
		const FGameplayEffectSpec Spec(GameplayEffect, EffectContext, Level);
		return ApplyTurnBasedGameplayEffectSpecToSelf(Spec, CustomDuration, PredictionKey);
	}

	return FActiveGameplayEffectHandle();
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectSpecToSelf(
	const FGameplayEffectSpec& Spec, const int32 CustomDuration, const FPredictionKey& PredictionKey)
{
	const FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToSelf(Spec, PredictionKey);
	if(ActiveGEHandle.WasSuccessfullyApplied())
	{
		// 将GE收纳至回合制容器中进行管理
		if (Spec.Def->DurationPolicy != EGameplayEffectDurationType::Instant)
		{
			TurnBasedActiveGameplayEffectsContainer.ApplyActiveGameplayEffect(ActiveGEHandle, Cast<UDGameplayEffect>(Spec.Def), CustomDuration);
			if (auto* Delegate = this->OnGameplayEffectRemoved_InfoDelegate(ActiveGEHandle))
			{
				Delegate->AddUObject(this, &UDAbilitySystemComponent::OnTurnBasedGameEffectRemoved);
			}
		}
	}

	return ActiveGEHandle;
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::K2_ApplyTurnBasedGameplayEffectToTarget(
	const TSubclassOf<UDGameplayEffect>& GameplayEffectClass, UDAbilitySystemComponent* Target, const int32 Level, const int32 CustomDuration, FGameplayEffectContextHandle EffectContext)
{
	if (Target == nullptr)
	{
		ABILITY_LOG(Log, TEXT("UAbilitySystemComponent::BP_ApplyGameplayEffectToTarget called with null Target. %s"), *GetFullName());
		return FActiveGameplayEffectHandle();
	}

	if (GameplayEffectClass == nullptr)
	{
		ABILITY_LOG(Error, TEXT("UAbilitySystemComponent::BP_ApplyGameplayEffectToTarget called with null GameplayEffectClass. %s"), *GetFullName());
		return FActiveGameplayEffectHandle();
	}

	if (!EffectContext.IsValid())
	{
		EffectContext = MakeEffectContext();
		EffectContext.AddInstigator(this->GetOwner(), this->GetOwner());
		EffectContext.AddActors({Target->GetOwner()});
		EffectContext.AddSourceObject(this);
	}

	const UDGameplayEffect* GameplayEffect = GameplayEffectClass->GetDefaultObject<UDGameplayEffect>();
	
	return ApplyTurnBasedGameplayEffectToTarget(GameplayEffect, Target, Level, CustomDuration, EffectContext);
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectToTarget(
	const UGameplayEffect *GameplayEffect,
	UDAbilitySystemComponent* Target,
	const int32 Level,
	const int32 CustomDuration,
	const FGameplayEffectContextHandle& Context,
	const FPredictionKey& PredictionKey) const
{
	check(GameplayEffect);
	if (HasNetworkAuthorityToApplyGameplayEffect(PredictionKey))
	{
		const FGameplayEffectSpec Spec(GameplayEffect, Context, Level);
		return ApplyTurnBasedGameplayEffectSpecToTarget(Spec, Target, CustomDuration, PredictionKey);
	}

	return FActiveGameplayEffectHandle();
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectSpecToTarget(
	const FGameplayEffectSpec& Spec,
	UDAbilitySystemComponent* Target,
	const int32 CustomDuration,
	FPredictionKey PredictionKey)
{
	const UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();
	if (!AbilitySystemGlobals.ShouldPredictTargetGameplayEffects())
	{
		// If we don't want to predict target effects, clear prediction key
		PredictionKey = FPredictionKey();
	}

	FActiveGameplayEffectHandle ReturnHandle;

	if (Target)
	{
		ReturnHandle = Target->ApplyTurnBasedGameplayEffectSpecToSelf(Spec, CustomDuration, PredictionKey);
	}

	return ReturnHandle;
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::BP_ApplyTurnBasedGameplayEffectSpecToSelf(
	const FGameplayEffectSpecHandle& SpecHandle, const int32 CustomDuration)
{
	FActiveGameplayEffectHandle ReturnHandle;
	if (SpecHandle.IsValid())
	{
		ReturnHandle = ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get(), CustomDuration);
	}

	return ReturnHandle;
}

FActiveGameplayEffectHandle UDAbilitySystemComponent::BP_ApplyTurnBasedGameplayEffectSpecToTarget(
	const FGameplayEffectSpecHandle& SpecHandle, UDAbilitySystemComponent* Target, const int32 CustomDuration)
{
	FActiveGameplayEffectHandle ReturnHandle;
	if (SpecHandle.IsValid() && Target)
	{
		ReturnHandle = ApplyTurnBasedGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), Target, CustomDuration);
	}

	return ReturnHandle;
}

bool UDAbilitySystemComponent::RemoveTurnBasedActiveGameplayEffect(
	const FActiveGameplayEffectHandle Handle,
	const int32 StacksToRemove)
{
	const bool bRemoveDone = RemoveActiveGameplayEffect(Handle, StacksToRemove);
	if (bRemoveDone)
	{
		TurnBasedActiveGameplayEffectsContainer.RemoveActiveGameplayEffect(Handle);
	}

	return bRemoveDone;
}

void UDAbilitySystemComponent::NetMulticast_FireAbilityProjectile_Implementation(
	const TSubclassOf<ADProjectile> ProjectileClass,
	const TSubclassOf<UDGameplayAbility> AbilityClass,
	AActor* Target,
	FVector TargetLocation,
	AActor* Caster,
	FVector StartLocation)
{
	if (Caster)
	{
		StartLocation = Caster->GetActorLocation();// Todo 获取骨骼上的Socket位置
	}
	if (Target)
	{
		TargetLocation = Target->GetActorLocation();// Todo 为了表现可以随机获取一个身体部位位置
	}

	const FVector Dir = (TargetLocation - StartLocation).GetSafeNormal();
	
	const FTransform SpawnTransform(Dir.Rotation(), StartLocation);
	ADProjectile* Projectile = GetWorld()->SpawnActor<ADProjectile>(ProjectileClass, SpawnTransform);
	Projectile->AbilityInstance = AbilityClass->GetDefaultObject<UDGameplayAbility>();
	Projectile->Caster = Caster;
	Projectile->Target = Target;
	Projectile->TargetLocation = TargetLocation;
}

void UDAbilitySystemComponent::OnTurnBasedGameEffectRemoved(const FGameplayEffectRemovalInfo& InGameplayEffectRemovalInfo)
{
	RemoveTurnBasedActiveGameplayEffect(InGameplayEffectRemovalInfo.ActiveEffect->Handle);
}

void UDAbilitySystemComponent::BattleBegin()
{
}

void UDAbilitySystemComponent::OnHit()
{
}

void UDAbilitySystemComponent::BeginTurn()
{
}

void UDAbilitySystemComponent::EndTurn()
{
}

void UDAbilitySystemComponent::NotifyAbilityFireOrHit(const UClass* AbilityClass) const
{
	OnAbilityReadyToFire.Broadcast(AbilityClass);
}

void UDAbilitySystemComponent::NotifyGameplayEffectAppliedToBP(
	UAbilitySystemComponent* Asc,
	const FGameplayEffectSpec& Spec,
	FActiveGameplayEffectHandle Handle) const
{
	OnGEAppliedCallback.Broadcast(Spec.Def->GetAssetTags().First(), Spec.Duration);
	//Spec.StackCount;
}

void UDAbilitySystemComponent::NotifyGameplayEffectRemovedToBP(const FActiveGameplayEffect& Effect) const
{
	OnGERemovedCallback.Broadcast(Effect.Spec.Def->GetAssetTags().First());
}

void UDAbilitySystemComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	// Fast Arrays don't use push model, but there's no harm in marking them with it.
	// The flag will just be ignored.
	FDoRepLifetimeParams Params;
	Params.bIsPushBased = true;

	Params.Condition = COND_Dynamic;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDAbilitySystemComponent, TurnBasedActiveGameplayEffectsContainer, Params);
	

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}