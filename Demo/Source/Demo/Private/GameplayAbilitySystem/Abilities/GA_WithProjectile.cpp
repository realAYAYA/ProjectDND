#include "GA_WithProjectile.h"

#include "AbilitySystemLog.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DProjectile.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_PlayMontageAndWait.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_WithTargetData.h"

UGA_WithProjectile::UGA_WithProjectile()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	//ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

	Montage = nullptr;
	MontageTask = nullptr;
	TargetDataTask = nullptr;
}

void UGA_WithProjectile::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (const auto* Asc = GetDAbilitySystemComponent(ActorInfo); !Asc)
		K2_CancelAbility();

	if (Montage)
	{
		auto* Task = UDAbilityTask_PlayMontageAndWait::CreateTask(this, TEXT("Ready"), Montage);
		Task->OnCompleted.AddDynamic(this, &UGA_WithProjectile::K2_EndAbility);
		Task->OnCancelled.AddDynamic(this, &UGA_WithProjectile::K2_CancelAbility);
		Task->OnInterrupted.AddDynamic(this, &UGA_WithProjectile::K2_CancelAbility);
		Task->OnBlendOut.AddDynamic(this, &UGA_WithProjectile::K2_EndAbility);
		ActiveTasks.Add(Task);
		MontageTask = Task;
		MontageTask->ReadyForActivation();

		//UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		//AnimInstance->OnPlayMontageNotifyBegin;;
	}

	auto* Task = UDAbilityTask_WithTargetData::CreateTask(this);
	Task->ValidData.AddDynamic(this, &UGA_WithProjectile::ReceiveTargetData);
	Task->Cancelled.AddDynamic(this, &UGA_WithProjectile::CancelTargetData);
	ActiveTasks.Add(Task);
	TargetDataTask = Task;
	Task->ReadyForActivation();
}

void UGA_WithProjectile::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UGA_WithProjectile::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;

	// Todo 检测数据合法性，取消技能
	// Todo 计算消耗 施加CD 抑或是因为法术反制施法失败，仍计算消耗，但不会施加效果
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	MontageSetNextSectionName(FName("Loop"), FName("OnFire"));
}

void UGA_WithProjectile::CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	K2_CancelAbility();
}

void UGA_WithProjectile::OnFire(UDAbilitySystemComponent* Asc)
{
	// 程序运行到该函数时不能保证Ability存有正确的Asc或Actor信息
	// Todo 法术施法成功进行结算，也可能被法术反制导致失败
	
	K2_FireProjectile(CacheTargetData, Asc->GetOwner());
}

void UGA_WithProjectile::BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, ADProjectile*& ProjectileActor)
{
	ProjectileActor = nullptr;
	
	if (UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (*Class != nullptr)
			ProjectileActor = World->SpawnActorDeferred<ADProjectile>(*Class, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	}

	if (ProjectileActor)
	{
		ProjectileActor->AbilityInstance = this;
	}
}

void UGA_WithProjectile::FinishSpawningProjectile(ADProjectile* ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (IsValid(ProjectileActor))
	{
		auto* Caster = Cast<ADCharacter>(this->GetDAbilitySystemComponent(CurrentActorInfo)->GetOwner());
		ProjectileActor->InitializeProjectile(this, Caster, TargetDataHandle);
		ProjectileActor->FinishSpawning(FTransform());
	}
}

ADCharacter* UGA_WithProjectile::GetDCharacter(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (ActorInfo)
		return Cast<ADCharacter>(ActorInfo->AvatarActor.Get());
	return nullptr;
}

UDAbilitySystemComponent* UGA_WithProjectile::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (const auto* Character = GetDCharacter(ActorInfo))
		return Character->GetDAbilitySystemComponent();
	return nullptr;
}

UWorld* UGA_WithProjectile::GetWorld() const
{
	return Super::GetWorld();
}
