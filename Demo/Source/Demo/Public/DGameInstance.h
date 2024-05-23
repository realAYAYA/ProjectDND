// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
};
