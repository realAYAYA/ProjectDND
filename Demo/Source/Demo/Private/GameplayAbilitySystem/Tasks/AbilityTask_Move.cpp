// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_Move.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GameplayAbilitySystem/TargetData/DTargetActor.h"

UAbilityTask_Move::UAbilityTask_Move()
{
	bTickingTask = true;
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

void UAbilityTask_Move::Activate()
{
	LastLocation = Caster->GetActorLocation();
	
	Super::Activate();
}

void UAbilityTask_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (Caster && Caster->GetAttributeSet())
	{
		auto* Att = Caster->GetAttributeSet();

		const FVector CurrentLocation = Caster->GetActorLocation();
		const float Distance = (CurrentLocation - LastLocation).Length();
		const float MoveCost = Att->GetMoveCost() * Distance;
		const float NewValue = Att->GetMoveDistance() - MoveCost;
		Att->SetMoveDistance(FMath::Clamp(NewValue, 0.0f, Att->GetMoveDistance()));
		LastLocation = CurrentLocation;
		
		if (Att->GetMoveDistance() > 0)
			return;
	}

	OnNoMoreMoveDistance.Broadcast();
	EndTask();
}
