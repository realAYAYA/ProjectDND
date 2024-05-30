#include "GA_WithTargetData.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_PlayMontageAndWait.h"
#include "GameplayAbilitySystem/Tasks/DAbilityTask_WithTargetData.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/TargetData/DTargetActor.h"

UGA_WithTargetData::UGA_WithTargetData()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	// LocalPredicted 适合客户端自行执行的技能
	// Server Init 适合由服务器触发，客户端随同执行的技能，尤其是被动技能（否则会触发失败）
	//ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

	Montage = nullptr;
	MontageTask = nullptr;
	TargetDataTask = nullptr;
}

void UGA_WithTargetData::BeginSpawningTargetActor(const TSubclassOf<ADTargetActor>& Class, APlayerController* PlayerController, const UDGameplayAbility* Ability, ADTargetActor*& OutTargetActor)
{
	if (!Class.Get() || !Ability || !Ability->IsInstantiated() || !Ability->GetCurrentAbilitySpec() || !PlayerController)
		return;

	const auto* Character = GetDCharacter(*Ability->GetCurrentActorInfo());
	if (!Character || !Character->IsPlayerControlled() || !Character->IsLocallyControlled())
		return;

	if (Character != PlayerController->GetPawn())
		return;// 施法者与玩家控制器不是同一个
	
	if (UWorld* World = Character->GetWorld())
	{
		if (*Class != nullptr)
			OutTargetActor = World->SpawnActorDeferred<ADTargetActor>(*Class, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	}

	if (IsValid(OutTargetActor))
	{
		OutTargetActor->InitTargetActor(PlayerController, Character->GetAbilitySystemComponent(), *Ability->GetCurrentAbilitySpec());
	}
}

void UGA_WithTargetData::FinishSpawningTargetActor(ADTargetActor* Actor)
{
	if (IsValid(Actor))
	{
		Actor->FinishSpawning(FTransform());
	}
}

bool UGA_WithTargetData::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Montage)
	{
		return false;
	}

	if (!GetDAbilitySystemComponent(*ActorInfo))
	{
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_WithTargetData::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 动画相关
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

	// TargetData
	{
		auto* Task = UDAbilityTask_WithTargetData::CreateTask(this);
		Task->ValidData.AddDynamic(this, &UGA_WithTargetData::ReceiveTargetData);
		Task->Cancelled.AddDynamic(this, &UGA_WithTargetData::CancelTargetData);
		ActiveTasks.Add(Task);
		TargetDataTask = Task;
		Task->ReadyForActivation();
	}

	// 设置角色ControlYaw，方便角色跟随镜头或鼠标转向（服务器端调用才有效）
	{
		GetDCharacter(*ActorInfo)->bUseControllerRotationYaw = true;
	}
}

void UGA_WithTargetData::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	// 设置角色ControlYaw，方便角色跟随镜头或鼠标转向（服务器端调用才有效）
	{
		GetDCharacter(*ActorInfo)->bUseControllerRotationYaw = false;
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_WithTargetData::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;
}

void UGA_WithTargetData::CancelTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	K2_CancelAbility();
}

void UGA_WithTargetData::OnReceiveAnimNotify(UDAbilitySystemComponent* Asc)
{
}
