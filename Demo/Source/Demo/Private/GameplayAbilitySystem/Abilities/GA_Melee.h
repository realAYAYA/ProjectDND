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

	/** 技能激活时赋予效果，结束时并不会主动移除*/
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TArray<TSubclassOf<UDGameplayEffect>> EffectsJustApplyOnStart;
	
	UGA_Melee();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
	virtual void OnReceiveAnimNotify(UDAbilitySystemComponent* Asc) override;

	// 根据TargetData, 执行命中逻辑
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ProjectD")
	bool HitTarget(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);
};