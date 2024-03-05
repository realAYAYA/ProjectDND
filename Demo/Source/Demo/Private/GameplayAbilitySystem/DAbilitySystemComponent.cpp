﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

void UDAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();


	TurnBasedActiveGameplayEffectsContainer.Owner = this;

	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::OnGEApplied);
	ActiveGameplayEffects.OnActiveGameplayEffectRemovedDelegate.AddUObject(this, &UDAbilitySystemComponent::OnGERemoved);
}

void UDAbilitySystemComponent::CheckTurnDurationExpired()
{
	TArray<int32> RemoveList;
	for (int32 i = 0; i < TurnBasedActiveGameplayEffectsContainer.GameplayEffects_Internal.Num(); i++)
	{
		FTurnBasedActiveGameplayEffect& TurnBasedActiveGameplayEffect = TurnBasedActiveGameplayEffectsContainer.GameplayEffects_Internal[i];
		const FActiveGameplayEffect* ActiveGameplayEffect = GetActiveGameplayEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle);

		const UDGameplayEffect* GameplayEffectDef = Cast<UDGameplayEffect>(ActiveGameplayEffect->Spec.Def);
		if (!GameplayEffectDef)
			continue;
		
		TurnBasedActiveGameplayEffect.CurrentTurn += 1;
		if (GameplayEffectDef->TurnPeriod > 0 && TurnBasedActiveGameplayEffect.CurrentTurn % GameplayEffectDef->TurnPeriod != 0)
		{
			// 施加周期效果
			ActiveGameplayEffects.ExecutePeriodicGameplayEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle);
		}

		if (TurnBasedActiveGameplayEffect.CurrentTurn == TurnBasedActiveGameplayEffect.DurationTurn)
		{
			RemoveActiveGameplayEffect(TurnBasedActiveGameplayEffect.ActiveGameplayEffectHandle, - 1);
			RemoveList.Add(i);
		}
	}

	for (const int32 Idx : RemoveList)
	{
		TurnBasedActiveGameplayEffectsContainer.GameplayEffects_Internal.RemoveAtSwap(Idx, 1, false);
	}
}

int32 UDAbilitySystemComponent::GetActiveEffectRemainingTurnAndDuration() const
{
	return 0;
}

bool UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectToSelf(const TSubclassOf<UDGameplayEffect>& GameplayEffectClass, const int32 Level)
{
	if (!GameplayEffectClass.Get())
		return false;

	const UDGameplayEffect* GameplayEffectDef = GameplayEffectClass->GetDefaultObject<UDGameplayEffect>();
	if (!GameplayEffectDef || GameplayEffectDef->DurationPolicy == EGameplayEffectDurationType::HasDuration)
		return false;
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
	EffectContextHandle.AddSourceObject(this->GetOwner());
	const FGameplayEffectSpecHandle SpecHandle = this->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);
	if (SpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if(ActiveGEHandle.WasSuccessfullyApplied())
		{
			// 将GE收纳至回合制容器中进行管理
			if (GameplayEffectDef->DurationPolicy != EGameplayEffectDurationType::Instant)
			{
				TurnBasedActiveGameplayEffectsContainer.ApplyActiveGameplayEffect(ActiveGEHandle, GameplayEffectDef);
			}
		}
	}
	
	return false;
}

bool UDAbilitySystemComponent::RemoveTurnBasedActiveGameplayEffect(
	FActiveGameplayEffectHandle Handle,
	int32 StacksToRemove)
{
	const bool bRemoveDone = Super::RemoveActiveGameplayEffect(Handle, StacksToRemove);
	if (bRemoveDone)
	{
		TurnBasedActiveGameplayEffectsContainer.RemoveActiveGameplayEffect(Handle);
	}

	return bRemoveDone;
}

bool UDAbilitySystemComponent::MoveBegin()
{
	FGameplayTagContainer Container;
	Container.AddTag(FGameplayTag::RequestGameplayTag(FName("GAS.Ability.Movement.Move")));
	
	return TryActivateAbilitiesByTag(Container, true);
}

void UDAbilitySystemComponent::MoveEnd()
{
	FGameplayTagContainer Container;
	Container.AddTag(FGameplayTag::RequestGameplayTag(FName("GAS.Ability.Movement.Move")));
	
	CancelAbilities(&Container);
}

void UDAbilitySystemComponent::Jump()
{
	FGameplayTagContainer Container;
	Container.AddTag(FGameplayTag::RequestGameplayTag(FName("GAS.Ability.Movement.Jump")));
	
	TryActivateAbilitiesByTag(Container, true);
}

void UDAbilitySystemComponent::JumpEnd()
{
	FGameplayTagContainer Container;
	Container.AddTag(FGameplayTag::RequestGameplayTag(FName("GAS.Ability.Movement.Jump")));
	
	CancelAbilities(&Container);
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

void UDAbilitySystemComponent::OnGEApplied(
	UAbilitySystemComponent* Asc,
	const FGameplayEffectSpec& Spec,
	FActiveGameplayEffectHandle Handle) const
{
	OnGEAppliedCallback.Broadcast(Spec.Def->GetAssetTags().First(), Spec.Duration);
	//Spec.StackCount;
}

void UDAbilitySystemComponent::OnGERemoved(const FActiveGameplayEffect& Effect) const
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