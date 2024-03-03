// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystemGlobalTags.h"
#include "DAbilitySystemComponent.generated.h"

class AMCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGEAppliedDelegate, const FGameplayTag&, Tag, const float, TimeRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGERemovedDelegate, const FGameplayTag&, Tag);

/**
 * 
 */
UCLASS()
class DEMO_API UDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void InitializeComponent() override;

	/** Whenever a duration based GE is added */
	UPROPERTY(BlueprintAssignable, Category = "ProjectT")
	FOnGEAppliedDelegate OnGEAppliedCallback;

	UPROPERTY(BlueprintAssignable, Category = "ProjectT")
	FOnGERemovedDelegate OnGERemovedCallback;

	void CheckTurnDurationExpired(FActiveGameplayEffectHandle Handle);

	UFUNCTION(Blueprintable, Category = "ProjectT")
	int32 GetActiveEffectTurnRemainingAndDuration() const;


	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey) override;

	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpec& GameplayEffect, UAbilitySystemComponent* Target, FPredictionKey PredictionKey) override;
	
	
	// 受到近战攻击时触发的效果
	
	// 受到近战攻击时给对方施加效果

	// 受到法术伤害时给对方施加效果

	// 近战攻击敌人时触发的效果

	// 攻击敌人时给对方施加效果

	// 施放法术时触发的效果
	
	bool MoveBegin();
	void MoveEnd();

	void Jump();
	void JumpEnd();

	void BeginTurn();

	void EndTurn();

protected:

	//void OnTakingMeleeAttack();

	//void OnTakingSpellAttack();

	//void OnTakingDamage();

	//void OnTakingHostileBehavior();

	

	void OnGEApplied(UAbilitySystemComponent* Asc, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle) const;

	void OnGERemoved(const FActiveGameplayEffect& Effect) const;
};
