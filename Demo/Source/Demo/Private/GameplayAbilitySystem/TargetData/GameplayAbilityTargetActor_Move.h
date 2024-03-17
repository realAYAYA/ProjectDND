// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_Move.generated.h"

/**
 * 
 */
UCLASS()
class AGameplayAbilityTargetActor_Move : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
};
