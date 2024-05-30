#pragma once

#include "CoreMinimal.h"
#include "DGameplayAbility.h"
#include "GA_WithTargetData.generated.h"

class ADTargetActor;
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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ProjectD")
	TSubclassOf<ADTargetActor> TargetActorClass;

	//  Can only be called on instanced abilities
	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	static void BeginSpawningTargetActor(const TSubclassOf<ADTargetActor>& Class, APlayerController* PlayerController, const UDGameplayAbility* Ability, ADTargetActor*& OutTargetActor);

	UFUNCTION(BlueprintCallable, Category = "ProjctD")
	static void FinishSpawningTargetActor(ADTargetActor* Actor);

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
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
	
	virtual void OnReceiveAnimNotify(UDAbilitySystemComponent* Asc);

protected:

	UPROPERTY()
	UDAbilityTask_PlayMontageAndWait* MontageTask;
};
