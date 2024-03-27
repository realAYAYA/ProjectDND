// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

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
	UAnimMontage* MontageOnAbilityStart;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageStandby;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* MontageOnFire;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY()
	ADCharacter* Target;
	
	UPROPERTY()
	UAbilityTask_WaitTargetData* TargetDataTask;

	UPROPERTY()
	EAbilityState AbilityState = EAbilityState::Standby;

	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);
};
