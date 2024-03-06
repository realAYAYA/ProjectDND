// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "DGameplayEffect.h"
#include "GameplayAbilitySystemGlobalTags.h"
#include "DAbilitySystemComponent.generated.h"

class ADCharacter;
class UDGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGEAppliedDelegate, const FGameplayTag&, Tag, const float, TimeRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGERemovedDelegate, const FGameplayTag&, Tag);

/**
 * 
 */
UCLASS(BlueprintType)
class DEMO_API UDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

#if WITH_EDITORONLY_DATA
	/**  */
	UPROPERTY(VisibleAnywhere, Transient, Category = "PorjectD")
	mutable FText Warning1 = LOCTEXT("Warning1", "警告: 不允许使用HasDuration特性以及自带的Period属性; 一旦使用，后果无法估测");

	UPROPERTY(VisibleAnywhere, Transient, Category = "PorjectD")
	mutable FText Warning2 = LOCTEXT("Warning2", "警告: 不允许使用ApplyGameplayEffectSpecToSelf()或ApplyGameplayEffectSpecToTarget()方法; 一旦使用，后果无法估测");
#endif

	virtual void InitializeComponent() override;

	/** Whenever a duration based GE is added */
	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnGEAppliedDelegate OnGEAppliedCallback;

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnGERemovedDelegate OnGERemovedCallback;

	// Only called by server
	void CheckTurnDurationExpired();

	void ExecuteTurnBasedPeriodicEffect(const FActiveGameplayEffectHandle& Handle);

	UFUNCTION(Blueprintable, Category = "ProjectD")
	int32 GetActiveEffectRemainingTurn(const FActiveGameplayEffectHandle& ActiveHandle) const;

	/** 回合制专用GE施加 */
	bool ApplyTurnBasedGameplayEffectToSelf(const TSubclassOf<UDGameplayEffect>& GameplayEffectClass, const int32 Level = 1, const int32 CustomDuration = -1);

	/** Removes GameplayEffect by Handle. StacksToRemove=-1 will remove all stacks. */
	bool RemoveTurnBasedActiveGameplayEffect(const FActiveGameplayEffectHandle Handle, const int32 StacksToRemove = -1);
	
	
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

private:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FTurnBasedActiveGameplayEffectsContainer TurnBasedActiveGameplayEffectsContainer;
};
