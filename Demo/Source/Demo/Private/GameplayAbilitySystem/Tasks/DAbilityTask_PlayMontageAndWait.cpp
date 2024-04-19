﻿#include "DAbilityTask_PlayMontageAndWait.h"
#include "GameplayAbilitySystem/Abilities/GA_WithTargetData.h"

#include "AbilitySystemGlobals.h"

UDAbilityTask_PlayMontageAndWait* UDAbilityTask_PlayMontageAndWait::CreateTask(
	UGA_WithTargetData* OwningAbility,
	const FName TaskInstanceName,
	UAnimMontage* MontageToPlay,
	float Rate,
	const FName StartSection,
	const bool bStopWhenAbilityEnds,
	const float AnimRootMotionTranslationScale,
	const float StartTimeSeconds,
	const bool bAllowInterruptAfterBlendOut)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UDAbilityTask_PlayMontageAndWait* MyObj = NewAbilityTask<UDAbilityTask_PlayMontageAndWait>(OwningAbility, TaskInstanceName);
	MyObj->Init(MontageToPlay, Rate, StartSection, bStopWhenAbilityEnds, AnimRootMotionTranslationScale, StartTimeSeconds, bAllowInterruptAfterBlendOut);
	return MyObj;
}

void UDAbilityTask_PlayMontageAndWait::Init(
	UAnimMontage* InMontageToPlay,
	const float InRate,
	const FName InStartSection,
	const bool InbStopWhenAbilityEnds,
	const float InAnimRootMotionTranslationScale,
	const float InStartTimeSeconds,
	const bool InbAllowInterruptAfterBlendOut)
{
	this->MontageToPlay = InMontageToPlay;
	this->Rate = InRate;
	this->StartSection = InStartSection;
	this->AnimRootMotionTranslationScale = InAnimRootMotionTranslationScale;
	this->bStopWhenAbilityEnds = InbStopWhenAbilityEnds;
	this->bAllowInterruptAfterBlendOut = InbAllowInterruptAfterBlendOut;
	this->StartTimeSeconds = InStartTimeSeconds;
}
