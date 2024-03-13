// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_Move.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

UAbilityTask_Move* UAbilityTask_Move::CreateMoveTask(
	UGameplayAbility* OwningAbility,
	ADCharacter* InCharacterOwner,
	const FVector InDestination)
{
	UAbilityTask_Move* Task = NewAbilityTask<UAbilityTask_Move>(OwningAbility);

	Task->bTickingTask = true;
	Task->Caster = InCharacterOwner; 
	Task->Destination = InDestination;

	//SetAbilitySystemComponent(InCharacterOwner)
	return Task;
}

void UAbilityTask_Move::Activate()
{
	Super::Activate();

	CastTime = 0;
	Caster->GetCharacterMovement()->MaxAcceleration = 1500000;
}

void UAbilityTask_Move::OnDestroy(bool bInOwnerFinished)
{
	Caster->GetCharacterMovement()->MaxAcceleration = 1500;
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!Caster)
	{
		Caster->GetCharacterMovement()->MaxAcceleration = 1500;
		//OnAbilityCancel.Broadcast();
		EndTask();
		return;
	}

	// Todo 计算移动消耗 扣除移动力

	CastTime += DeltaTime;
	
}
