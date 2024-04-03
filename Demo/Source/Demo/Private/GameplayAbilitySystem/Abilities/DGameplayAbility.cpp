#include "DGameplayAbility.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_PlayMontageAndWait.h"

void UDGameplayAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto* Asc = GetDAbilitySystemComponent(ActorInfo);
	if (!Asc)
		K2_CancelAbility();

	if (Montage)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Ready"), Montage);
		//Task->OnCompleted.AddDynamic(this, &UDGameplayAbility::MontageToStandby);
		Task->OnCancelled.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		Task->OnInterrupted.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		//Task->OnBlendOut.AddDynamic(this, &UDGameplayAbility::MontageToStandby);
		ActiveTasks.Add(Task);
		MontageTask = Task;
		MontageTask->Activate();

		Asc->OnAbilityReadyToFire.AddDynamic(this, &UDGameplayAbility::OnFire);
	}
}

void UDGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	if (auto* Asc = GetDAbilitySystemComponent(ActorInfo))
	{
		Asc->OnAbilityReadyToFire.RemoveDynamic(this, &UDGameplayAbility::OnFire);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UDGameplayAbility::ParseTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	const auto* Character = GetDCharacter(CurrentActorInfo);
	if (Character && Montage)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_SetNextSection(FName("Loop"), FName("OnFire"), Montage);

		// Todo 计算消耗 施加CD 抑或是因为法术反制施法失败，仍计算消耗，但不会施加效果
	}
}

void UDGameplayAbility::CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	K2_CancelAbility();
}

void UDGameplayAbility::OnFire(const UClass* AbilityClass)
{
	// Todo 法术施法成功进行结算，也可能被法术反制导致失败
}

ADCharacter* UDGameplayAbility::GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (ActorInfo)
		return Cast<ADCharacter>(ActorInfo->AvatarActor.Get());
	return nullptr;
}

UDAbilitySystemComponent* UDGameplayAbility::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (const auto* Character = GetDCharacter(ActorInfo))
		return Character->AbilitySystemComponent;
	return nullptr;
}
