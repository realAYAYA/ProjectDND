// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DGameTypes.h"
#include "DInventoryFunctionLiabrary.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category= "ProjectD")
	static float CalculateItemWeight(const FDInventoryItem& Item);

	//static float CalculateItemWeight(const FInventoryItemBase& Item);
};