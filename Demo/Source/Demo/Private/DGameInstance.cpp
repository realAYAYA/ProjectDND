// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameInstance.h"

#include "AbilitySystemGlobals.h"

void UDGameInstance::Init()
{
	Super::Init();

	UAbilitySystemGlobals::Get().InitGlobalData();

	
}
