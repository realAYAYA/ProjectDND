#include "DAbilityTask_WithTargetData.h"

#include "AbilitySystemComponent.h"

UDAbilityTask_WithTargetData::UDAbilityTask_WithTargetData()
{
	TargetClass = AGameplayAbilityTargetActor::StaticClass();
	TargetActor = nullptr;
	ConfirmationType = EGameplayTargetingConfirmation::UserConfirmed;
}

UDAbilityTask_WithTargetData* UDAbilityTask_WithTargetData::CreateTask(UGameplayAbility* OwningAbility)
{
	UDAbilityTask_WithTargetData* MyObj = NewAbilityTask<UDAbilityTask_WithTargetData>(OwningAbility, FName("Move"));

	MyObj->Ability = OwningAbility;
	MyObj->AbilitySystemComponent = OwningAbility->GetAbilitySystemComponentFromActorInfo();
	MyObj->TaskOwner = OwningAbility;
	
	return MyObj;
}

void UDAbilityTask_WithTargetData::Activate()
{
	if (Ability)
	{
		RegisterTargetDataCallbacks();// 注册回调，允许服务器接收来自客户端的TargetData
		return;
		
		if (ShouldSpawnTargetActor())
		{
			//RegisterTargetDataCallbacks();
			
			/*if (TargetClass != nullptr)
			{
				if (UWorld* World = GEngine->GetWorldFromContextObject(Ability.Get(), EGetWorldErrorMode::LogAndReturnNull))
				{
					//TargetActor = World->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
					//TargetActor = World->SpawnActor<AGameplayAbilityTargetActor>(TargetClass);
				}
			}

			if (TargetActor)
			{
				InitializeTargetActor(TargetActor.Get());
				FinalizeTargetActor(TargetActor.Get());
				return;
			}*/
		}
	}
	
	EndTask();
}
