// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_WithTargetData.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DProjectile.h"
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
	UFUNCTION(BlueprintNativeEvent, Category = "ProjectD")
	bool FireProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);

	UFUNCTION(BlueprintCallable, Category = "ProjctD|GA_WithProjectile")
	virtual void ApplyGameplayEffectToTarget(ADCharacter* Caster, ADCharacter* Target, ADProjectile* Projectile);

protected:

	bool bDoOnceAnimNotify = false;// Todo FixMe: 联机下，客户端施法时，主机会触为其发两次动画通知
};
