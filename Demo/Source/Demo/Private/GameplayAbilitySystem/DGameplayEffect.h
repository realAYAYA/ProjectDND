// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "DGameplayEffect.generated.h"

#define INFINITY_TURN -1

UENUM(BlueprintType)
enum class EMBuffType : uint8
{
	None		UMETA(Displayname = "None"),	// 用于无法被驱散的效果
	Spell		UMETA(Displayname = "Spell"),
	Combat		UMETA(Displayname = "Combat"),
};

UENUM(BlueprintType)
enum class EMDamageType : uint8
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
 * Turn-based Active GameplayEffect instance
 *	-回合制专用GE实例
 *	-基于回合制记录GE的生命周期
 *  -Replication callbacks
 */
USTRUCT(BlueprintType)
struct DEMO_API FTurnBasedActiveGameplayEffect : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 TurnDuration = INFINITY_TURN;

	UPROPERTY()
	int32 StartTurn = 1;

	UPROPERTY()
	int32 Handle = -1;

	UPROPERTY()
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle;
};

USTRUCT()
struct DEMO_API FTurnBasedActiveGameplayEffectsContainer : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY();

	
private:
	
	UPROPERTY()
	TArray<FTurnBasedActiveGameplayEffect>	GameplayEffects_Internal;
};

/**
 * 
 */
UCLASS()
class DEMO_API UDGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PorjectM")
	EMDamageType DamageType;
	
	// Todo 目标和施术者
	// Todo 持续，且影响双方的buff，例如：吸血
	// Todo 如果是持续性效果，如何取得运行时执行了第几秒（次）

	// Todo 暴击机制

	
};