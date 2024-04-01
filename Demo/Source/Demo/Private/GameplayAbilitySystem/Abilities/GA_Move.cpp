// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Move.h"
#include "Character/DCharacter.h"
#include "DPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GameplayAbilitySystem/GameplayAbilitySystemGlobalTags.h"
#include "GameplayAbilitySystem/Tasks/AbilityTask_Move.h"

UGA_Move::UGA_Move()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	AbilityTags.AddTag(FGameplayAbilityGlobalTags::GetPreConstruct().Move);
}

bool UGA_Move::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!IsInstantiated())
		return false;
	
	bool Result = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!Result)
		return Result;
	
	const ADCharacter* Caster = Cast<ADCharacter>(ActorInfo->AvatarActor);
	if (!Caster)
		return false;

	Result = Caster->GetAttributeSet()->GetMoveDistance() > 0 ? true : false;
	
	return Result;
}

void UGA_Move::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* OwnerInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	MoveTask = UAbilityTask_Move::CreateTask(this);
	MoveTask->OnNoMoreMoveDistance.AddDynamic(this, &UGA_Move::K2_CancelAbility);
	this->ActiveTasks.Add(MoveTask);
	MoveTask->ReadyForActivation();
	

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}

void UGA_Move::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	// 停止移动
	const ADCharacter* Caster = Cast<ADCharacter>(CurrentActorInfo->AvatarActor);
	if (Caster->GetPlayerState())
	{
		if (const auto* PC = Cast<ADPlayerController>(Caster->GetPlayerState()->GetPlayerController()))
			PC->StopMove();
	}

	if (MoveTask)
		MoveTask->EndTask();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
