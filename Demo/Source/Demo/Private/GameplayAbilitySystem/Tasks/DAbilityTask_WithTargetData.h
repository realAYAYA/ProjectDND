// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "DAbilityTask_WithTargetData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCancel);

/**
 * 
 */
UCLASS()
class UDAbilityTask_WithTargetData : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityTaskEnd;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnd OnAbilityCancel;
	
	UPROPERTY()
	class ADCharacter* Caster;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	AGameplayAbilityTargetActor* GetTargetActor() const { return TargetActor.Get(); }
};
