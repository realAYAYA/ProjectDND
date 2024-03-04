// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

#include "AbilitySystemStats.h"
#include "DGameplayEffect.h"

void UDAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::OnGEApplied);
	ActiveGameplayEffects.OnActiveGameplayEffectRemovedDelegate.AddUObject(this, &UDAbilitySystemComponent::OnGERemoved);
}

void UDAbilitySystemComponent::CheckTurnDurationExpired(FActiveGameplayEffectHandle Handle)
{
	
}

int32 UDAbilitySystemComponent::GetActiveEffectTurnRemainingAndDuration() const
{
	return 0;
}

bool UDAbilitySystemComponent::ApplyTurnBasedGameplayEffectToSelf(const TSubclassOf<UDGameplayEffect>& GameplayEffectClass)
{
	if (!GameplayEffectClass.Get())
		return false;

	const UDGameplayEffect* GameplayEffectDef = GameplayEffectClass->GetDefaultObject<UDGameplayEffect>();
	if (!GameplayEffectDef)
		return false;
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
	EffectContextHandle.AddSourceObject(this->GetOwner());
	const FGameplayEffectSpecHandle SpecHandle = this->MakeOutgoingSpec(GameplayEffectDef, EffectContextHandle);
	if (SpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if(ActiveGEHandle.WasSuccessfullyApplied())
		{
			// 将GE收纳至回合制容器中进行管理
			if (GameplayEffectDef->DurationPolicy != EGameplayEffectDurationType::Instant)
			{
				
			}
		}
	}
	
	return false;
}

FGameplayEffectSpecHandle UDAbilitySystemComponent::MakeOutgoingSpec(
	const UDGameplayEffect* GameplayEffectObject,
	FGameplayEffectContextHandle Context) const
{
	SCOPE_CYCLE_COUNTER(STAT_GetOutgoingSpec);
	if (Context.IsValid() == false)
	{
		Context = MakeEffectContext();
	}

	if (GameplayEffectObject)
	{
		FGameplayEffectSpec* NewSpec = new FGameplayEffectSpec(GameplayEffectObject, Context, GameplayEffectObject->Level);
		return FGameplayEffectSpecHandle(NewSpec);
	}

	return FGameplayEffectSpecHandle(nullptr);
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
