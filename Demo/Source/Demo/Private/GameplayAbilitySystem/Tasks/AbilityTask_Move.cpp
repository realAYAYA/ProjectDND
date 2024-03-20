// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_Move.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GameplayAbilitySystem/TargetData/DTargetActor.h"

UAbilityTask_Move::UAbilityTask_Move()
{
	Caster = nullptr;
}

UAbilityTask_Move* UAbilityTask_Move::CreateTask(UGameplayAbility* OwningAbility)
{
	UAbilityTask_Move* MyObj = NewAbilityTask<UAbilityTask_Move>(OwningAbility, FName("Move"));
	
	MyObj->Ability = OwningAbility;
	MyObj->AbilitySystemComponent = OwningAbility->GetAbilitySystemComponentFromActorInfo();
	MyObj->TaskOwner = OwningAbility;
	MyObj->Caster = Cast<ADCharacter>(MyObj->AbilitySystemComponent->GetOwnerActor());
	
	return MyObj;
}

void UAbilityTask_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (Caster && Caster->GetAttributeSet())
	{
		const auto* Att = Caster->GetAttributeSet();
		if (Att->GetMoveDistance() > 0)
			return;
	}

	OnNoMoreMoveDistance.Broadcast();
	EndTask();
}
