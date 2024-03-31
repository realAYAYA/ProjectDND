#include "DAbilityTask_PlayMontageAndWait.h"

UDAbilityTask_PlayMontageAndWait::UDAbilityTask_PlayMontageAndWait()
{
}

UDAbilityTask_PlayMontageAndWait* UDAbilityTask_PlayMontageAndWait::CreateTask(
	UDGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	UAnimMontage* MontageToPlay,
	float Rate,
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale,
	float StartTimeSeconds,
	bool bAllowInterruptAfterBlendOut)
{
	return nullptr;
}

void UDAbilityTask_PlayMontageAndWait::Activate()
{
	// Todo
	
	Super::Activate();
}
