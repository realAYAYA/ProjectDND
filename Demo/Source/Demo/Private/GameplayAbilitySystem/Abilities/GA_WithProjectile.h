// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_WithTargetData.h"
#include "GA_WithProjectile.generated.h"

class UDAbilityTask_WithTargetData;
class UDAbilityTask_PlayMontageAndWait;
class ADProjectile;
class UDAbilitySystemComponent;
class ADCharacter;
class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;

/**
 * 
 */
UCLASS()
class UGA_WithProjectile : public UGA_WithTargetData
{
	GENERATED_BODY()

public:

	UGA_WithProjectile();

	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
	virtual void OnReceiveAnimNotify(UDAbilitySystemComponent* Asc) override;

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	static void BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, UGA_WithProjectile* Ability, ADProjectile*& ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	static void FinishSpawningProjectile(ADProjectile* ProjectileActor);
	
	// 根据TargetData, 执行发射逻辑(Server Only)
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "ProjectD")
	bool FireProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);
	
};
