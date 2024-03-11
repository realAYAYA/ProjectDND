// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

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
