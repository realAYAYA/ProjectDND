// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
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
class UGA_WithProjectile : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UGA_WithProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* Montage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY()
	ADCharacter* Target;
	
	// Todo 技能被打断

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	virtual void OnFire(const UClass* AbilityClass);

	UFUNCTION()
	virtual void ProcessProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);

	// 根据TargetData, 执行发射逻辑
	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "ProcessProjectile", meta=(ScriptName = "ProcessProjectile"))
	void K2_ProcessProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);

	static ADCharacter* GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo);
	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);

protected:

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageTask;

	UPROPERTY()
	UDAbilityTask_WithTargetData* TargetDataTask;

	FGameplayAbilityTargetDataHandle CacheTargetData;
};
