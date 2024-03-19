// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAbilityTask_WithTargetData.h"
#include "AbilityTask_Move.generated.h"

/**
 * 
 */
UCLASS()
class UAbilityTask_Move : public UDAbilityTask_WithTargetData
{
	GENERATED_BODY()

public:

	UAbilityTask_Move();

	UFUNCTION(BlueprintCallable, Category = "ProjectD", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_Move* CreateMoveTask(UGameplayAbility* OwningAbility, ADCharacter* Character);

	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;
	
};
