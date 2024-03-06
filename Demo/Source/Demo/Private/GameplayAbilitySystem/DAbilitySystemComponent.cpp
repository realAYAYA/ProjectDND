// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

void UDAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	TurnBasedActiveGameplayEffectsContainer.RegisterWithOwner(this);
	TurnBasedActiveGameplayEffectsContainer.SetIsUsingReplicationCondition(true);

	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::OnGEApplied);
	ActiveGameplayEffects.OnActiveGameplayEffectRemovedDelegate.AddUObject(this, &UDAbilitySystemComponent::OnGERemoved);
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
				TurnBasedActiveGameplayEffectsContainer.ApplyActiveGameplayEffect(ActiveGEHandle, GameplayEffectDef, CustomDuration);
			}
		}
	}
	
	return false;
}

bool UDAbilitySystemComponent::RemoveTurnBasedActiveGameplayEffect(
	const FActiveGameplayEffectHandle Handle,
	const int32 StacksToRemove)
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