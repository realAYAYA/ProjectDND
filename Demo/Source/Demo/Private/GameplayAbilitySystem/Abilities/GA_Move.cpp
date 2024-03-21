// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Move.h"
#include "Character/DCharacter.h"
#include "DPlayerController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "GameFramework/PlayerState.h"
#include "GameplayAbilitySystem/GameplayAbilitySystemGlobalTags.h"
#include "GameplayAbilitySystem/GameplayEffects/GE_Move.h"
#include "GameplayAbilitySystem/Tasks/AbilityTask_Move.h"
#include "GameplayAbilitySystem/Tasks/AbilityTask_Move_WithTargetData.h"

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
		Result = false;

	const auto* PC = Cast<ADPlayerController>(Caster->GetPlayerState()->GetPlayerController());
	if (!PC)
		Result = false;
	
	return Result;
}

void UGA_Move::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* OwnerInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	MoveTask = UAbilityTask_Move::CreateTask(this);
	MoveTask->OnNoMoreMoveDistance.AddDynamic(this, &UGA_Move::K2_EndAbility);
	this->ActiveTasks.Add(MoveTask);
	MoveTask->ReadyForActivation();

	// 施加GE
	UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	const FGameplayEffectContextHandle TargetEffectContext = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(UGE_Move::StaticClass(), 0, TargetEffectContext);
	if (SpecHandle.IsValid())
	{
		MoveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (!MoveGEHandle.WasSuccessfullyApplied())
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Effect to Target %s"), *GetName(), *GetNameSafe(UGE_Move::StaticClass()));
	}


	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}

void UGA_Move::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 移除GE
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (MoveGEHandle.IsValid())
		ASC->RemoveActiveGameplayEffect(MoveGEHandle);
	
	// 停止移动
	const ADCharacter* Caster = Cast<ADCharacter>(CurrentActorInfo->AvatarActor);
	if (Caster->GetPlayerState())
	{
		if (const auto* PC = Cast<ADPlayerController>(Caster->GetPlayerState()->GetPlayerController()))
			PC->StopMove();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
