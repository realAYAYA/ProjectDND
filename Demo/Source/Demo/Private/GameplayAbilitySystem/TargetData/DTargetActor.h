// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "DTargetActor.generated.h"

class UDGameplayAbility;
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
	bool SetAbilityInfo(APlayerController* PC, UAbilitySystemComponent* Asc, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	bool SetAbilityInfoByClass(APlayerController* PC, UAbilitySystemComponent* Asc, const TSubclassOf<UDGameplayAbility>& AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "ProjectD", DisplayName = "ConfirmTargeting")
	void K2_ConfirmTargeting(const FGameplayAbilityTargetDataHandle& InTargetDataHandle);

	virtual void ConfirmTargetingAndContinue() override;// 必须被重写

private:

	UPROPERTY()
	FGameplayAbilityTargetDataHandle TargetDataHandle;
};
