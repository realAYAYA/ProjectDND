// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "DGameTypes.h"
#include "DPlayerController.generated.h"

class UPathFollowingComponent;
class ADCharacter;
class ATurnBasedBattleInstance;
/**
 * 
 */
UCLASS()
class ADPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ADPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Reset() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void PostNetInit() override;

	virtual void OnUnPossess() override;

	virtual void OnRep_Pawn() override;

	bool MoveTo(const FVector& GoalLocation) const;
	void StopMove() const;

private:

	/** Component used for moving along a path. */
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
	
public:

	// 检查当前控制的角色是否处于战斗中
	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	bool InBattle() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "YourTurn")
	void K2_YourTurn(const ADCharacter* InCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "OnBattle")
	void K2_OnBattle(const ADCharacter* InCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "BattleEnd")
	void K2_OnBattleEnd(const ADCharacter* InCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "ProjectD", DisplayName = "ReqTurnEnd")
	void K2_TurnEnd();

	UFUNCTION(Server, Reliable)
	void Server_TurnEnd();

	UFUNCTION()
	void Client_MyTurn(const ADCharacter* InCharacter);

	// Steam | Ps4 | XBox
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "ProjectD")
	int64 PlayerId = 0;
	
private:
	
	UFUNCTION(Server, Reliable)
	void ClientSendPlayerInfo();

	UFUNCTION(NetMulticast, Reliable)
	void ServerSendPlayerInfo();

	static TMap<uint64, FDPlayerData> PlayerMap;
};
