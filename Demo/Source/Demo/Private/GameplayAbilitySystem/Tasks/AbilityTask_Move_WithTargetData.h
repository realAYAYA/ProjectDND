// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "AbilityTask_Move_WithTargetData.generated.h"

class ADCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCancel);

/**
 * 
 */
UCLASS()
class UDAbilityTask_Move_WithTargetData : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:

	UDAbilityTask_Move_WithTargetData();
	
	static UDAbilityTask_Move_WithTargetData* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;

	UPROPERTY()
	ADCharacter* Caster;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	AGameplayAbilityTargetActor* GetTargetActor() const { return TargetActor.Get(); }
};
