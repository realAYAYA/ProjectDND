// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DAbilityTask_PlayMontageAndWait.generated.h"

class UDGameplayAbility;
class ADCharacter;

/**
 * 
 */
UCLASS()
class UDAbilityTask_PlayMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:

	UDAbilityTask_PlayMontageAndWait();

	// On Ability Fire or Hit
	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnAbilityFire;
	
	static UDAbilityTask_PlayMontageAndWait* CreateTask(
		UDGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f,
		float StartTimeSeconds = 0.f,
		bool bAllowInterruptAfterBlendOut = false);
	
	virtual void Activate() override;
	
};