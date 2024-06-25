// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectTypes.h"
#include "DAbilitySystemBlueprintLibrary.generated.h"

struct FActiveGameplayEffectHandle;

/**
 * 
 */
UCLASS()
class UDAbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Returns the total turn for a given GameplayEffect */
	UFUNCTION(BlueprintCallable, Category = "ProjectD|GAS")
	static int32 GetActiveGameplayEffectTotalTurn(FActiveGameplayEffectHandle ActiveHandle);

	/** Returns the remaining turn for a given GameplayEffect */
	UFUNCTION(BlueprintCallable, Category = "ProjectD|GAS")
	static int32 GetActiveGameplayEffectRemainingTurn(FActiveGameplayEffectHandle ActiveHandle);

	UFUNCTION(BlueprintPure, Category = "ProjectD|EffectContext", Meta = (DisplayName = "HasCirtHit"))
	static bool EffectContextHasCritHit(FGameplayEffectContextHandle EffectContext, float& CirtValue);
};
