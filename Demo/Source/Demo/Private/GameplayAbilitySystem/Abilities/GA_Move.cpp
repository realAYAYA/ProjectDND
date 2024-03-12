// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Move.h"

#include "GameplayAbilitySystem/Tasks/AbilityTask_Move.h"

void UGA_Move::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	/*// 根据目标位置，计算冲锋的目的地
	FVector Destination = Target->GetActorLocation();
	//const float Radius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius() + 5.0f;
	const FVector Dir = UKismetMathLibrary::Normal(Target->GetActorLocation() - Caster->GetActorLocation(), 0.0001);
	Destination = Destination - Dir * Radius;

	// Task
	ChargeTask = UAbilityTask_Move::CreateMoveTask(this, Caster, Destination);
	ChargeTask->ReadyForActivation();// 启动任务*/
}

void UGA_Move::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_Move::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
