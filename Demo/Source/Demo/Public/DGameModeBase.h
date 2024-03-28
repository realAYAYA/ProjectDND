// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"

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

	UPROPERTY()
	TArray<class ATurnBasedBattleInstance*> BattleInstances;
};
