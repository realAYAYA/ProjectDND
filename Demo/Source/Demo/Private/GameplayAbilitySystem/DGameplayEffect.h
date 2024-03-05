// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "DGameplayEffect.generated.h"

#define LOCTEXT_NAMESPACE "DGameplayEffect"
#define INFINITY_TURN -1

class UDGameplayEffect;
class UDAbilitySystemComponent;
struct FTurnBasedActiveGameplayEffectsContainer;

UENUM(BlueprintType)
enum class EMBuffType : uint8
{
	None		UMETA(Displayname = "None"),	// 用于无法被驱散的效果
	Spell		UMETA(Displayname = "Spell"),
	Combat		UMETA(Displayname = "Combat"),
};

UENUM(BlueprintType)
enum class EDDamageType : uint8
{
	Physical	UMETA(Displayname = "Physical"),
	Frost		UMETA(Displayname = "Frost"),
	Flame		UMETA(Displayname = "Flame"),
	Nature		UMETA(Displayname = "Nature"),
	Divine		UMETA(Displayname = "Divine"),
	Shadow		UMETA(Displayname = "Shadow"),
	Chaos		UMETA(Displayname = "Chaos"),
};

/**
 * 解释：GAS对GE的维护由UAbilitySystemComponent中的一组FActiveGameplayEffect（基于FastArray）的同步实现的
 * 驱动方式是通过FTimer来进行持续时间和周期的计算，而回合制则需要根据Runtime下的回合数进行驱动
 * 问题在于，根据对GAS的研究，FActiveGameplayEffect实现过于底层很难进行拓展
 * 针对于此，作者的思路是按照FActiveGameplayEffect数组的思路实现一组与之平行存在的数据，该组数据则仅仅对回合制驱动下的相关数据进行追踪
 * 回合制下的buff被移除的情形具体可分为：1.回合时间消耗完；2.Stack归零；3.被外力移除
 */

/**
 * Turn-based Active GameplayEffect instance
 *	-回合制专用GE实例
 *	-基于回合制记录GE的生命周期
 *  -Replication callbacks
 */
USTRUCT(BlueprintType)
struct DEMO_API FTurnBasedActiveGameplayEffect : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	FTurnBasedActiveGameplayEffect()
		: ActiveGameplayEffectHandle(INDEX_NONE)
	{
		
	}

	FTurnBasedActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle, const int32 Period = 1, const int32 Duration = INFINITY_TURN)
	{
		ActiveGameplayEffectHandle = Handle;
		DurationTurn = Duration;
	}

	void PreReplicatedRemove(const FTurnBasedActiveGameplayEffectsContainer &InArray);
	void PostReplicatedAdd(const FTurnBasedActiveGameplayEffectsContainer &InArray);
	void PostReplicatedChange(const FTurnBasedActiveGameplayEffectsContainer &InArray);

	UPROPERTY()
	int32 CurrentTurn = 0;
	
	UPROPERTY()
	int32 DurationTurn = INFINITY_TURN;

	UPROPERTY()
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle;
};

USTRUCT()
struct DEMO_API FTurnBasedActiveGameplayEffectsContainer : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY();

	FTurnBasedActiveGameplayEffect* GetActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle);
	const FTurnBasedActiveGameplayEffect* GetActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle) const;

	FTurnBasedActiveGameplayEffect* ApplyActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle, const UDGameplayEffect* GameplayEffect);

	bool RemoveActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle);

	void CheckTurnDuration();
	
	UPROPERTY()
	TArray<FTurnBasedActiveGameplayEffect>	GameplayEffects_Internal;

	UPROPERTY()
	UDAbilitySystemComponent* Owner = nullptr;
};


/**
 * 回合制战斗专用GE
 * 
 */
UCLASS()
class DEMO_API UDGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:

	UDGameplayEffect();

#if WITH_EDITORONLY_DATA
	/** Allow us to show the Status of the class (valid configurations or invalid configurations) while configuring in the Editor */
	UPROPERTY(VisibleAnywhere, Transient, Category = "PorjectT")
	mutable FText Warning = LOCTEXT("Warning", "警告: 不允许使用HasDuration特性以及自带的Period属性; 一旦使用，后果无法估测");
#endif

	/** 技能等级/环数 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PorjectT")
	int32 Level = 1;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PorjectT")
	EDDamageType DamageType = EDDamageType::Physical;

	/** 持续回合数 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PorjectT", meta=(EditCondition="DurationPolicy != EGameplayEffectDurationType::Instant", EditConditionHides))
	int32 TurnDuration = 1;

	/**
	 * 周期触发，每多少回合触发一次. 0代表施加该GE后直到移除前持续有效
	 * 例如，寒冰护甲，buff生效期间护甲始终+2，设置为0即可
	 * 例如，暴风雪，每回合需要造成伤害的，需要设置为1
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PorjectT", meta=(EditCondition="DurationPolicy != EGameplayEffectDurationType::Instant", EditConditionHides))
	int32 TurnPeriod = 0;
	
	// Todo 目标和施术者
	// Todo 持续，且影响双方的buff，例如：吸血
	// Todo 如果是持续性效果，如何取得运行时执行了第几秒（次）
	// Todo 暴击机制
};