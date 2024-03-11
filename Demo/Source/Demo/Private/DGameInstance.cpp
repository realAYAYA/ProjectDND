// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameInstance.h"

#include "DCharacterManager.h"

void UDGameInstance::Init()
{
	Super::Init();

	CharacterManager = NewObject<UDCharacterManager>(this);
	CharacterManager->Init();
}
