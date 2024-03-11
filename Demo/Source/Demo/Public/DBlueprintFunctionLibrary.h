// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBlueprintFunctionLibrary.generated.h"

class UDCharacterManager;
class UDGameInstance;
class ADCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API UDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category= "ProjectD", meta = (WorldContext = "WorldContextObject"))
	static UDGameInstance* GetDGameInstance(const UObject* WorldContextObject);

	/** 给定Id, 查找关卡中的角色*/
	UFUNCTION(BlueprintCallable, Category= "ProjectD", meta = (WorldContext = "WorldContextObject"))
	static ADCharacter* FindCharacterByRoleId(const UObject* WorldContextObject, const int64 Id);

	UFUNCTION(BlueprintCallable, Category= "ProjectD", meta = (WorldContext = "WorldContextObject"))
	static UDCharacterManager* GetCharacterManager(const UObject* WorldContextObject);
};
