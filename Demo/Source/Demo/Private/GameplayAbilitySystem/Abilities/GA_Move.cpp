// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GA_Move.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "DPlayerController.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "GameplayAbilitySystem/GameplayEffects/GE_Move.h"
#include "GameplayAbilitySystem/Tasks/AbilityTask_Move.h"

UGA_Move::UGA_Move()
{
	// Todo GameplayTage;
}

bool UGA_Move::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	bool Result = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!Result)
		return Result;
	
	const ADCharacter* Caster = Cast<ADCharacter>(ActorInfo->AvatarActor);
	const auto* PC = Cast<ADPlayerController>(CurrentActorInfo->PlayerController.Get());
	if (!Caster || !PC)
		Result = false;
	
	return Result;
}

void UGA_Move::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* OwnerInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	// Task
	UAbilityTask_Move* TargetData = UAbilityTask_Move::CreateMoveTask(this);
	TargetData->Activate();
	this->ActiveTasks.Add(TargetData);

	TargetData->ValidData.AddDynamic(this, &UGA_Move::ConfirmMove);
	TargetData->Cancelled.AddDynamic(this, &UGA_Move::CancelMove);
	
	TargetData->ReadyForActivation();// 启动任务
}

void UGA_Move::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 移除GE
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (MoveGEHandle.IsValid())
		ASC->RemoveActiveGameplayEffect(MoveGEHandle);
	
	// 停止移动
	const auto* PC = Cast<ADPlayerController>(CurrentActorInfo->PlayerController.Get());
	PC->StopMove();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Move::ConfirmMove(const FGameplayAbilityTargetDataHandle& Data)
{
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

	const auto* HitResult = Data.Get(0)->GetHitResult();
	if (!HitResult)
	{
		CancelMove(Data);
		return;
	}

	// 开始移动
	const auto* PC = Cast<ADPlayerController>(CurrentActorInfo->PlayerController.Get());
	if (!PC->MoveTo(HitResult->Location))
	{
		CancelMove(Data);
	}
}	

void UGA_Move::CancelMove(const FGameplayAbilityTargetDataHandle& Data)
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}
