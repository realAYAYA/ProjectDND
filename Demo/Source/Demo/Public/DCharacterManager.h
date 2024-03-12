// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacterManager.generated.h"

class ADCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSpawn, int64, Id);

/**
 * 
 */
UCLASS(BlueprintType)
class UDCharacterManager : public UObject
{
	GENERATED_BODY()

public:

	void Init();

	void Reset();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	ADCharacter* Find(const int64 Id);

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnCharacterSpawn OnCharacterSpawn;

	void RegisterCharacter(const int64 Id, ADCharacter* In);

	void UnRegisterCharacter(const int64 Id);

	int64 GenerateRoleId();// Only called by server

	void Foreach(const TFunction<bool(ADCharacter*)>& InFunc);

private:
	
	UPROPERTY()
	TMap<int64, ADCharacter*> Characters;

	int64 SerialNum = 0;
};
