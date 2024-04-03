#include "GA_Fireball.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DProjectile.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_WithTargetData.h"

UGA_Fireball::UGA_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGA_Fireball::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto* Task = UDAbilityTask_WithTargetData::CreateTask(this);
	Task->ValidData.AddDynamic(this, &UGA_Fireball::ParseTargetData);
	Task->Cancelled.AddDynamic(this, &UGA_Fireball::CancelTargetData);
	ActiveTasks.Add(Task);
	TargetDataTask = Task;
	Task->Activate();
}

void UGA_Fireball::OnFire(const UClass* AbilityClass)
{
	if (AbilityClass && AbilityClass != this->StaticClass())
		return;

	const FVector TargetLoc = CacheTargetData.Get(0)->GetHitResult()->Location;
	
	if (ProjectileClass.Get())
	{
		UDAbilitySystemComponent* Asc = GetDAbilitySystemComponent(CurrentActorInfo);
		Asc->NetMulticast_FireAbilityProjectile(ProjectileClass, this->StaticClass(), nullptr, TargetLoc, Asc->GetOwner(), FVector());
	}
	else
	{
		// Todo 近战攻击的命中GE
	}
}
