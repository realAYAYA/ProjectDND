// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	virtual void OnUnPossess() override;

	virtual void OnRep_Pawn() override;

private:

	/** Component used for moving along a path. */
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "YourTurn")
	void K2_YourTurn(const ADCharacter* InCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "OnBattle")
	void K2_OnBattle(const ADCharacter* InCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "BattleEnd")
	void K2_BattleEnd(const ADCharacter* InCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "ProjectD", DisplayName = "TurnEnd")
	void K2_TurnEnd();

	UFUNCTION(Server, Reliable)
	void ReqTurnEnd();

	void GetInBattle(ATurnBasedBattleInstance* BattleInstance);
	
	UFUNCTION(Client, Reliable)
	void OnBattle(const ADCharacter* InCharacter);

	UFUNCTION(Client, Reliable)
	void YourTurn(const ADCharacter* InCharacter);// Called by Server

	UFUNCTION(Client, Reliable)
	void BattleEnd();
	
};
