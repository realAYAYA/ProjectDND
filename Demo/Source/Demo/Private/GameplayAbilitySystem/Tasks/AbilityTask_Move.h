// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_Move.generated.h"

class ADCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveTaskEnd);

/**
 * 
 */
UCLASS()
class UAbilityTask_Move : public UAbilityTask
{
	GENERATED_BODY()

public:

	UAbilityTask_Move();
	
	static UAbilityTask_Move* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY()
	FOnMoveTaskEnd OnNoMoreMoveDistance;

	UPROPERTY()
	FOnMoveTaskEnd OnArrivedDestination;
	
	UPROPERTY()
	ADCharacter* Caster;

	FVector LastLocation;

	FVector Destination;
};
