// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGameplayAbilityWithTargetData.h"
#include "GA_Move.generated.h"

class UAbilityTask_Move;
/**
 * 
 */
UCLASS()
class UGA_Move : public UDGameplayAbilityWithTargetData
{
	GENERATED_BODY()

public:

	UGA_Move();
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	
	virtual void ConfirmTargetData(const FGameplayAbilityTargetDataHandle& Data) override;

	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& Data) override;
	
	FActiveGameplayEffectHandle MoveGEHandle;
};
