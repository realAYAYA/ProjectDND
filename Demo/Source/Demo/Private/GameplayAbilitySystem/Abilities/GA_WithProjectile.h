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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;
	
	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
	virtual void OnReceiveAnimNotify(UDAbilitySystemComponent* Asc) override;

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	void BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, ADProjectile*& ProjectileActor);

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	void FinishSpawningProjectile(ADProjectile* ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	// 根据TargetData, 执行发射逻辑
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ProjectD")
	void FireProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);
	
};
