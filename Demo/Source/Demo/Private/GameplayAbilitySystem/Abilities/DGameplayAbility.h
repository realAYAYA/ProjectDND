// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

class ADCharacter;
class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;

/**
 * 
 */
UCLASS()
class UDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:

	// 动画通知识别名，用于查找，响应AnimNotifyClass逻辑
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectD")
	FString AnimNotifyName;
};
