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

	/** 技能命中时，施加的GE*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TArray<TSubclassOf<UDGameplayEffect>> EffectsOnHit;

	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
	virtual void OnReceiveAnimNotify(UDAbilitySystemComponent* Asc) override;

	// 根据TargetData, 执行命中逻辑
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ProjectD|GAS|Melee")
	bool ReceiveHitTarget(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);

	virtual float CalculateHitRate(const ADCharacter* Caster, const ADCharacter* Target) override;

	virtual float CalculateCritRate(const ADCharacter* Caster, const ADCharacter* Target) override;
};