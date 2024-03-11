// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacterManager.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class UDCharacterManager : public UObject
{
	GENERATED_BODY()

public:

	void Init();

	void Reset();

	ADCharacter* Find(const int64 Id);

	void RegisterCharacter(const int64 Id, ADCharacter* In);

	void UnRegisterCharacter(const int64 Id);

	int64 GenerateRoleId();// Only called by server

private:
	
	UPROPERTY()
	TMap<int64, ADCharacter*> Characters;

	int64 SerialNum = 0;
};
