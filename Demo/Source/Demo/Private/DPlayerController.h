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

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void K2_TurnEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD")
	void ClientOnBattle();
	
	UFUNCTION(Client, Reliable)
	void NotifyOnBattle();
	void GetInBattle(ATurnBasedBattleInstance* BattleInstance);

	UFUNCTION(Client, Reliable)
	void NotifyYourTurn(const ADCharacter* InCharacter);
	void YourTurn(const ADCharacter* InCharacter);// Called by Server

	UFUNCTION(Client, Reliable)
	void BattleEnd();

	UFUNCTION(Server, Reliable)
	void ReqTurnEnd();
	
};
