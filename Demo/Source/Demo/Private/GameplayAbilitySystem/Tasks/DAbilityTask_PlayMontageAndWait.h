// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DAbilityTask_PlayMontageAndWait.generated.h"

class UGA_WithTargetData;
class ADCharacter;

/**
 * 
 */
UCLASS()
class UDAbilityTask_PlayMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:

	// On Ability Fire or Hit
	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnAbilityFire;
	
	static UDAbilityTask_PlayMontageAndWait* CreateTask(
		UGA_WithTargetData* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f,
		float StartTimeSeconds = 0.f,
		bool bAllowInterruptAfterBlendOut = false);

	void Init(
		UAnimMontage* InMontageToPlay,
		float InRate = 1.f,
		FName InStartSection = NAME_None,
		bool InbStopWhenAbilityEnds = true,
		float InAnimRootMotionTranslationScale = 1.f,
		float InStartTimeSeconds = 0.f,
		bool InbAllowInterruptAfterBlendOut = false);
	
};