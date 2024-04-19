// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_WithTargetData.h"
#include "GA_Melee.generated.h"

/**
 * 近战类技能
 */
UCLASS()
class UGA_Melee : public UGA_WithTargetData
{
	GENERATED_BODY()

public:

	UGA_Melee();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
	virtual void OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc) override;
};