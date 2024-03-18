// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "AbilityTask_Move.generated.h"

class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCancel);

/**
 * 
 */
UCLASS()
class UAbilityTask_Move : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:

	UAbilityTask_Move();

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityTaskEnd;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityCancel;

	UFUNCTION(BlueprintCallable, Category = "ProjectD", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_Move* CreateMoveTask(UGameplayAbility* OwningAbility, ADCharacter* Character);

	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;
	
	UPROPERTY()
	ADCharacter* Caster;
	
};
