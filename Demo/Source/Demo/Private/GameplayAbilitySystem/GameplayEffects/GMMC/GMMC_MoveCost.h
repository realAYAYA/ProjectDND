// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMC_MoveCost.generated.h"

/**
 * 
 */
UCLASS()
class UGMMC_MoveCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UGMMC_MoveCost();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	
	FGameplayEffectAttributeCaptureDefinition MoveCost;
};
