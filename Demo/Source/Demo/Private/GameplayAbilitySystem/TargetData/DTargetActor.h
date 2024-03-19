// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "DTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ADTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	ADTargetActor(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	bool SetAbilityInfo(APlayerController* PC, const UAbilitySystemComponent* Asc, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = "ProjectD", DisplayName = "ConfirmTargeting")
	void K2_ConfirmTargeting(const FGameplayAbilityTargetDataHandle& InTargetDataHandle);

	virtual void ConfirmTargetingAndContinue() override;

private:

	UPROPERTY()
	FGameplayAbilityTargetDataHandle TargetDataHandle;
};
