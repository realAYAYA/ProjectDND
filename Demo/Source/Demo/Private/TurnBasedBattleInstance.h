// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "GameFramework/Actor.h"
#include "TurnBasedBattleInstance.generated.h"

class ADCharacter;
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
	
	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	int32 GetCurrentTurnNum() const { return CurrentTurnNum; }

	UPROPERTY(ReplicatedUsing = OnCurrentCharacterChange)
	ADCharacter* CurrentCharacter;

	UPROPERTY()
	TArray<ADCharacter*> CharacterList;

	UPROPERTY(ReplicatedUsing = OnCharacterListChange)
	TArray<int32> CharacterIdList;

	UPROPERTY(ReplicatedUsing = OnTurnNumChanged)
	int32 CurrentTurnNum = 0;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void BeginBattle();// 战斗开始
	
	void TurnEnd(const ADCharacter* InCharacter);

	void YourTurn(ADCharacter* InCharacter);// 下一个单位的回合

	UFUNCTION()
	void OnCurrentCharacterChange();

	UFUNCTION()
	void OnCharacterListChange();

	UFUNCTION()
	void OnTurnNumChanged();

	// 合并两场战斗
	void MergeBattle(ATurnBasedBattleInstance* In);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void PostNetInit() override;
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
