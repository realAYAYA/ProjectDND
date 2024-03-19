// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbilityWithTargetData.generated.h"

class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;
/**
 * 
 */
UCLASS()
class UDGameplayAbilityWithTargetData : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void ConfirmTargetData(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& Data);
	
	FActiveGameplayEffectHandle MoveGEHandle;

	UPROPERTY()
	UAbilityTask_WaitTargetData* TargetDataTask;
};
