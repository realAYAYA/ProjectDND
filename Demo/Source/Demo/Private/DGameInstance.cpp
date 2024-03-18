// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameInstance.h"

#include "AbilitySystemGlobals.h"
#include "DCharacterManager.h"

void UDGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData();

	CharacterManager = NewObject<UDCharacterManager>(this);
	CharacterManager->Init();
}
