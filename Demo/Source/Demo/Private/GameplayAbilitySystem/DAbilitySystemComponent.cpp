// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

#include "Abilities/DGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Net/UnrealNetwork.h"

void UDAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	TurnBasedActiveGameplayEffectsContainer.RegisterWithOwner(this);
	TurnBasedActiveGameplayEffectsContainer.SetIsUsingReplicationCondition(true);

	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::OnGEApplied);
	ActiveGameplayEffects.OnActiveGameplayEffectRemovedDelegate.AddUObject(this, &UDAbilitySystemComponent::OnGERemoved);
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

bool UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectToSelf(
	const TSubclassOf<UDGameplayEffect>& GameplayEffectClass,
	const int32 Level,
	const int32 CustomDuration)
{
	if (!GameplayEffectClass.Get())
		return false;

	// 回合制GAS不支持HasDuration
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
				TurnBasedActiveGameplayEffectsContainer.ApplyActiveGameplayEffect(*SpecHandle.Data.Get(), ActiveGEHandle, GameplayEffectDef, CustomDuration);
			}
		}
	}
	
	return false;
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