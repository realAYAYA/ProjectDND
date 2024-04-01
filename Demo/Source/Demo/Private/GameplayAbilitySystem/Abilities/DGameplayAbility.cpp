﻿#include "DGameplayAbility.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DProjectile.h"
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

	if (MontageStart)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Ready"), MontageStart);
		Task->OnCompleted.AddDynamic(this, &UDGameplayAbility::MontageToStandby);
		Task->OnCancelled.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		Task->OnInterrupted.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		Task->OnBlendOut.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		ActiveTasks.Add(Task);
		MontageStartTask = Task;
		MontageStartTask->Activate();
	}

	if (MontageStandby)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Standby"), MontageStandby);
		Task->OnCompleted.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);// maybe unuseful
		Task->OnCancelled.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		Task->OnInterrupted.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		Task->OnBlendOut.AddDynamic(this, &UDGameplayAbility::K2_CancelAbility);
		ActiveTasks.Add(Task);
		MontageLoopTask = Task;
	}

	if (MontageFire)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Fire"), MontageFire);
		Task->OnCompleted.AddDynamic(this, &UDGameplayAbility::K2_EndAbility);
		Task->OnCancelled.AddDynamic(this, &UDGameplayAbility::K2_EndAbility);
		Task->OnInterrupted.AddDynamic(this, &UDGameplayAbility::K2_EndAbility);
		Task->OnBlendOut.AddDynamic(this, &UDGameplayAbility::K2_EndAbility);
		ActiveTasks.Add(Task);
		MontageFireTask = Task;
		
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
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDGameplayAbility::MontageToStandby()
{
	if (MontageLoopTask)
	{
		MontageLoopTask->Activate();
	}

	K2_EndAbility();
}

void UDGameplayAbility::OnFire(const UClass* AbilityClass)
{
	if (AbilityClass && AbilityClass != this->StaticClass())
		return;

	if (ProjectileClass.Get())
	{
		auto* Asc = GetDAbilitySystemComponent(CurrentActorInfo);
		Asc->NetMulticast_FireAbilityProjectile(ProjectileClass, this->StaticClass(), Target, FVector(), Asc->GetOwner(), FVector());
	}
	else
	{
		// Todo 近战攻击的命中GE
	}
}

UDAbilitySystemComponent* UDGameplayAbility::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (ActorInfo)
	{
		if (const auto* Character = Cast<ADCharacter>(ActorInfo->AvatarActor.Get()))
			return Character->AbilitySystemComponent;
	}

	return nullptr;
}