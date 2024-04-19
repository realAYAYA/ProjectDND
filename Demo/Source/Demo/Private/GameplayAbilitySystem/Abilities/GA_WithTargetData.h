#pragma once

#include "CoreMinimal.h"
#include "DGameplayAbility.h"
#include "GA_WithTargetData.generated.h"

class UDAbilityTask_WithTargetData;
class UDAbilityTask_PlayMontageAndWait;
class ADProjectile;
class UDAbilitySystemComponent;
class ADCharacter;
class UAbilityTask_WaitTargetData;
class UAbilityTask_Move;

/**
 * 需要客户端玩家发送TargetData确认执行的技能类
 */
UCLASS()
class UGA_WithTargetData : public UDGameplayAbility
{
	GENERATED_BODY()

public:

	UGA_WithTargetData();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// 留意客户端下的AbilityActorInfo等变量是没有被进行初始化的（或同步）
	static ADCharacter* GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo);
	static UDAbilitySystemComponent* GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo);

protected:


	// TargetData

public:

	UFUNCTION()
	virtual void ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	virtual void CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
protected:

	UPROPERTY()
	UDAbilityTask_WithTargetData* TargetDataTask;

	FGameplayAbilityTargetDataHandle CacheTargetData;


	// Animation
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	UAnimMontage* Montage;
	
	virtual void OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc);

protected:

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageTask;
};
