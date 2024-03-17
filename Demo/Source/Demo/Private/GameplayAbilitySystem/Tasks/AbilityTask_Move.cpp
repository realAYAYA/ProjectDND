// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_Move.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/TargetData/GameplayAbilityTargetActor_Move.h"

UAbilityTask_Move::UAbilityTask_Move()
{
	this->TargetClass = AGameplayAbilityTargetActor_Move::StaticClass();
	this->TargetActor = nullptr;
	this->ConfirmationType = EGameplayTargetingConfirmation::Instant;
}

UAbilityTask_Move* UAbilityTask_Move::CreateMoveTask(UGameplayAbility* OwningAbility)
{
	UAbilityTask_Move* MyObj = NewAbilityTask<UAbilityTask_Move>(OwningAbility, FName("Move"));
	
	return MyObj;
}

void UAbilityTask_Move::Activate()
{
	Super::Activate();

	if (Ability)
	{
		if (ShouldSpawnTargetActor())
		{
			if (TargetClass != nullptr)
			{
				if (UWorld* World = GEngine->GetWorldFromContextObject(Ability.Get(), EGetWorldErrorMode::LogAndReturnNull))
				{
					TargetActor = World->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				}
			}

			if (TargetActor)
			{
				InitializeTargetActor(TargetActor);
			}
		}

		RegisterTargetDataCallbacks();
	}
}

void UAbilityTask_Move::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
}
