// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

class UDGameplayEffect;
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
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	FString AnimNotifyName;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	int32 Level = 1;

	/** 技能激活时赋予效果，结束时并不会主动移除*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TArray<TSubclassOf<UDGameplayEffect>> EffectsJustApplyOnStart;
	
	/** 技能激活期间赋予的效果，结束时主动移除*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TArray<TSubclassOf<UDGameplayEffect>> EffectsRemoveOnEnd;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// 被动触发技能很有用的函数
	//virtual bool ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const;

private:

	TArray<FActiveGameplayEffectHandle> EffectHandlesRemoveOnEnd;
};
