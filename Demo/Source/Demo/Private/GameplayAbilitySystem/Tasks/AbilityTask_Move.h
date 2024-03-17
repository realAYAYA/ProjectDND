// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "AbilityTask_Move.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class UAbilityTask_Move : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:

	UAbilityTask_Move();

	UFUNCTION(BlueprintCallable, Category = "ProjectD", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_Move* CreateMoveTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	virtual void TickTask(float DeltaTime) override;
	
};
