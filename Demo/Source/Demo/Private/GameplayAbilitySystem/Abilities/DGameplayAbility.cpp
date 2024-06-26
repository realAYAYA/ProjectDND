#include "DGameplayAbility.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/GameplayEffects/DGameplayEffect.h"

#include "AbilitySystemLog.h"
#include "Character/DCharacter.h"

bool UDGameplayAbility::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	const UDAbilitySystemComponent* Asc = Cast<UDAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (!Asc)
		return false;
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UDGameplayAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UDAbilitySystemComponent* Asc = Cast<UDAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());

	FGameplayEffectContextHandle EffectContext = Asc->MakeEffectContext();
	EffectContext.SetAbility(this);
	EffectContext.AddInstigator(ActorInfo->AvatarActor.Get(), ActorInfo->AvatarActor.Get());
	EffectContext.AddSourceObject(this);
	
	// 处理技能开始时施加效果
	for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsJustApplyOnStart)
	{
		if (!GameplayEffect.Get())
			continue;
		
		const FGameplayEffectSpecHandle SpecHandle = Asc->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
		if (!SpecHandle.IsValid())
			continue;
		
		FActiveGameplayEffectHandle ActiveGEHandle = Asc->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (!ActiveGEHandle.WasSuccessfullyApplied())
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
	}
	
	if (this->IsInstantiated())
	{
		for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsRemoveOnEnd)
		{
			if (!GameplayEffect.Get())
				continue;
		
			const FGameplayEffectSpecHandle SpecHandle = Asc->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
			if (!SpecHandle.IsValid())
				continue;
		
			FActiveGameplayEffectHandle ActiveGEHandle = Asc->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			if (!ActiveGEHandle.WasSuccessfullyApplied())
				ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));

			EffectHandlesRemoveOnEnd.Add(ActiveGEHandle);
		}
	}
}

void UDGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	// 移除技能GE
	if (IsInstantiated())
	{
		UDAbilitySystemComponent* Asc = Cast<UDAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
		for (FActiveGameplayEffectHandle& ActiveGEHandle : EffectHandlesRemoveOnEnd)
		{
			if (ActiveGEHandle.IsValid())
			{
				Asc->RemoveTurnBasedActiveGameplayEffect(ActiveGEHandle);
			}
		}

		EffectHandlesRemoveOnEnd.Empty();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


ADCharacter* UDGameplayAbility::GetDCharacter(const FGameplayAbilityActorInfo& ActorInfo)
{
	return Cast<ADCharacter>(ActorInfo.AvatarActor.Get());
}

UDAbilitySystemComponent* UDGameplayAbility::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo& ActorInfo)
{
	if (const auto* Character = GetDCharacter(ActorInfo))
		return Character->GetDAbilitySystemComponent();
	
	return nullptr;
}

AActor* UDGameplayAbility::ParseOneTargetTargetData(const FGameplayAbilityTargetDataHandle& TargetData)
{
	if (TargetData.IsValid(0) && TargetData.Get(0)->GetActors().Num() > 0)
	{
		return TargetData.Get(0)->GetActors()[0].Get();
	}
	
	return nullptr;
}

FVector UDGameplayAbility::ParseClickLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetData)
{
	if (TargetData.IsValid(0) && TargetData.Get(0)->HasHitResult())
	{
		return TargetData.Get(0)->GetHitResult()->Location;
	}
	
	return FVector();
}

float UDGameplayAbility::CalculateHitRate(const ADCharacter* Caster, const ADCharacter* Target)
{
	return 1.0f;
}

float UDGameplayAbility::CalculateCritRate(const ADCharacter* Caster, const ADCharacter* Target)
{
	return 0.0f;
}
