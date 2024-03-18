// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "GameplayAbilityTargetActor_Move.generated.h"

/**
 * 
 */
UCLASS()
class AGameplayAbilityTargetActor_Move : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	AGameplayAbilityTargetActor_Move(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void ConfirmTargetingAndContinue() override;
};
