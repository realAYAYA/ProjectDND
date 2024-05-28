// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "GameFramework/Actor.h"
#include "TurnBasedBattleInstance.generated.h"

class UGameplayEffect;
class ADCharacter;
/**
 * 一个回合下的信息
 * 如果角色队列中连续几个角色是同一阵营，则支持多个同阵营角色同时行动
 */
USTRUCT(BlueprintType)
struct FTurnBasedInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	int32 CurrentIndex = 0;// 当前进行回合的所有角色中最后一个的数组下标

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	TArray<int32> ActivatedCharacters;

	bool operator==(const FTurnBasedInfo& Right) const
	{
		if (CurrentIndex != Right.CurrentIndex)
			return false;

		return true;
	}
};

/**
* 回合制战斗实例
* 生成一场战斗，管理参与各个战斗单位
* 驱动回合推进
*/
UCLASS()
class DEMO_API ATurnBasedBattleInstance : public AActor
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	ATurnBasedBattleInstance();

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "ProjectD")
	int32 CurrentTurnNum = 0;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CharacterList, Category = "ProjectD")
	TArray<int32> CharacterList;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnTurnInfoChanged, Category = "ProjectD")
	FTurnBasedInfo CurrentTurnInfo;

	// 战斗开始. Server only
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ProjectD")
	void BeginBattle();
	
	void Server_TurnEnd(const ADCharacter* InCharacter);

	void Server_YourTurn(ADCharacter* InCharacter);// 通知角色回合开始

	bool IsMyTurn(const ADCharacter* InCharacter) const;// 查询当前回合是否为当前角色

	void SomeoneDied(const ADCharacter* InCharacter);

	UFUNCTION()
	void OnRep_CharacterList();

	UFUNCTION()
	void OnTurnInfoChanged();

	// 合并两场战斗
	void MergeBattle(ATurnBasedBattleInstance* In);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostNetInit() override;
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int32 FindCharacter(const int32 Id, ADCharacter*& Out) const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
