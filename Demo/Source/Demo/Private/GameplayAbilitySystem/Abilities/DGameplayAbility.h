// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

class UDAbilityTask_PlayMontageAndWait;
class ADProjectile;
class UDAbilitySystemComponent;
class ADCharacter;
class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	Standby		UMETA(Displayname = "Standby"),				// 技能随时可以发射
	HasBeenInterrupted	UMETA(Displayname = "Interrupt"),	// 技能已经被打断，法术反制
};

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

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageFire;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY()
	ADCharacter* Target;
	
	UPROPERTY()
	UAbilityTask_WaitTargetData* TargetDataTask;

	UPROPERTY()
	EAbilityState AbilityState = EAbilityState::Standby;

	// Todo 技能被打断

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	virtual void MontageToStandby();

	UFUNCTION()
	virtual void OnFire(const UClass* AbilityClass);
	
	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);


private:

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageStartTask;

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageLoopTask;

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageFireTask;
};
