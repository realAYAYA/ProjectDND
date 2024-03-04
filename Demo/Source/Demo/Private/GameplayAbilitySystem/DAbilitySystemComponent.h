// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystemGlobalTags.h"
#include "DAbilitySystemComponent.generated.h"

class AMCharacter;
class UDGameplayEffect;

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
	
	bool ApplyTurnBasedGameplayEffectToSelf(const TSubclassOf<UDGameplayEffect>& GameplayEffectClass);

	FGameplayEffectSpecHandle MakeOutgoingSpec(const UDGameplayEffect* GameplayEffectObject, FGameplayEffectContextHandle Context) const;
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

	void BattleBegin();

	void OnHit();

	/** 回合开始，施加回合制效果等*/
	void BeginTurn();

	/** 回合结束，施加回合制效果等*/
	void EndTurn();

protected:

	//void OnTakingMeleeAttack();

	//void OnTakingSpellAttack();

	//void OnTakingDamage();

	//void OnTakingHostileBehavior();

	

	void OnGEApplied(UAbilitySystemComponent* Asc, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle) const;

	void OnGERemoved(const FActiveGameplayEffect& Effect) const;
};
