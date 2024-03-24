// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGameplayAbility.h"
#include "GA_Fireball.generated.h"


class ADCharacter;
class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;

/**
 * 
 */
UCLASS()
class UGA_Fireball : public UDGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	
	UFUNCTION()
	void OnFire(const UClass* AbilityClass);
	
};
