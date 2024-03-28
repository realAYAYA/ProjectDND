// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"

class ATurnBasedBattleInstance;

/**
 * 
 */
UCLASS()
class DEMO_API ADGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void BuildBattleWithAllCharacters();

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<ATurnBasedBattleInstance> BattleInstanceClass;
	
	UPROPERTY()
	TArray<ATurnBasedBattleInstance*> BattleInstances;
};
