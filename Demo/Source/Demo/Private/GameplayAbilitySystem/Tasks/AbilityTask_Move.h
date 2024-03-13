// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_Move.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class UAbilityTask_Move : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ProjectD", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_Move* CreateMoveTask(UGameplayAbility* OwningAbility, ADCharacter* InCharacterOwner, FVector InDestination);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	virtual void TickTask(float DeltaTime) override;

protected: 

	UPROPERTY()
	ADCharacter* Caster;

	FVector Destination;

	float CastTime;
};
