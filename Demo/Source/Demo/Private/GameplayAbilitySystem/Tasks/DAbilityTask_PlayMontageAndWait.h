// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "DAbilityTask_PlayMontageAndWait.generated.h"

class ADCharacter;

/**
 * 
 */
UCLASS()
class UDAbilityTask_PlayMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:

	UDAbilityTask_PlayMontageAndWait();
	
	static UDAbilityTask_PlayMontageAndWait* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	
};