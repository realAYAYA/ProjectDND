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
	
	// Todo 技能被打断

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	virtual void OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc);

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	void BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, ADProjectile*& ProjectileActor);

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	void FinishSpawningProjectile(ADProjectile* ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	// 根据TargetData, 执行发射逻辑
	UFUNCTION(BlueprintImplementableEvent, Category = "ProjectD", DisplayName = "FireProjectile", meta=(ScriptName = "FireProjectile"))
	void K2_FireProjectile(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster);

	// 留意客户端下的AbilityActorInfo等变量是没有被进行初始化的（或同步）
	static ADCharacter* GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo);
	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);

protected:
	
	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageTask;

	UPROPERTY()
	UDAbilityTask_WithTargetData* TargetDataTask;

	FGameplayAbilityTargetDataHandle CacheTargetData;
};
