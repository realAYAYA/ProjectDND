#include "GA_WithTargetData.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_PlayMontageAndWait.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_WithTargetData.h"
#include "Character/DCharacter.h"

UGA_WithTargetData::UGA_WithTargetData()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	//ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

	Montage = nullptr;
	MontageTask = nullptr;
	TargetDataTask = nullptr;
}

void UGA_WithTargetData::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 动画相关
	if (Montage)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Ready"), Montage);
		Task->OnCompleted.AddDynamic(this, &UGA_WithTargetData::K2_EndAbility);
		Task->OnCancelled.AddDynamic(this, &UGA_WithTargetData::K2_CancelAbility);
		Task->OnInterrupted.AddDynamic(this, &UGA_WithTargetData::K2_CancelAbility);
		Task->OnBlendOut.AddDynamic(this, &UGA_WithTargetData::K2_EndAbility);
		ActiveTasks.Add(Task);
		MontageTask = Task;
		MontageTask->ReadyForActivation();
	}
	else
	{
		K2_CancelAbility();// 没有动画资产会导致发动技能失败
	}

	// TargetData
	{
		auto* Task = UDAbilityTask_WithTargetData::CreateTask(this);
		Task->ValidData.AddDynamic(this, &UGA_WithTargetData::ReceiveTargetData);
		Task->Cancelled.AddDynamic(this, &UGA_WithTargetData::CancelTargetData);
		ActiveTasks.Add(Task);
		TargetDataTask = Task;
		Task->ReadyForActivation();
	}
}

void UGA_WithTargetData::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


ADCharacter* UGA_WithTargetData::GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (ActorInfo)
		return Cast<ADCharacter>(ActorInfo->AvatarActor.Get());
	return nullptr;
}

UDAbilitySystemComponent* UGA_WithTargetData::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (const auto* Character = GetDCharacter(ActorInfo))
		return Character->GetDAbilitySystemComponent();
	
	return nullptr;
}

void UGA_WithTargetData::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;
}

void UGA_WithTargetData::CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	K2_CancelAbility();
}

void UGA_WithTargetData::OnNotifyReceivedWithComponent(UDAbilitySystemComponent* Asc)
{
}
