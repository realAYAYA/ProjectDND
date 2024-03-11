// Fill out your copyright notice in the Description page of Project Settings.


#include "DBlueprintFunctionLibrary.h"

#include "DCharacterManager.h"
#include "DGameInstance.h"

UDGameInstance* UDBlueprintFunctionLibrary::GetDGameInstance(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World ? Cast<UDGameInstance>(World->GetGameInstance()) : nullptr;
}

ADCharacter* UDBlueprintFunctionLibrary::FindCharacterByRoleId(const UObject* WorldContextObject, const int64 Id)
{
	if (const auto* GameInstance = GetDGameInstance(WorldContextObject))
	{
		GameInstance->CharacterManager->Find(Id);
	}
	
	return nullptr;
}

UDCharacterManager* UDBlueprintFunctionLibrary::GetCharacterManager(const UObject* WorldContextObject)
{
	if (const auto* GameInstance = GetDGameInstance(WorldContextObject))
		return GameInstance->CharacterManager;

	return nullptr;
}
