// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnBasedBattleInstance.generated.h"

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

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	int32 GetCurrentTurnNum() const { return CurrentTurnNum; }
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(ReplicatedUsing = OnTurnNumChanged)
	int32 CurrentTurnNum = 0;

	UFUNCTION()
	void OnTurnNumChanged();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
