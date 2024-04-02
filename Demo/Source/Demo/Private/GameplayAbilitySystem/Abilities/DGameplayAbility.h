// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

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
class UDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageStart;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageStandby;

	// Or hit
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageFire;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY()
	ADCharacter* Target;
	
	// Todo 技能被打断

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	virtual void MontageToStandby();

	UFUNCTION()
	virtual void ParseTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	virtual void OnFire(const UClass* AbilityClass);// or OnHit
	
	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);

protected:

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageStartTask;

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageLoopTask;

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageFireTask;

	UPROPERTY()
	UDAbilityTask_WithTargetData* TargetDataTask;

	FGameplayAbilityTargetDataHandle CacheTargetData;
};
