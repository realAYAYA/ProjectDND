#include "AbilityTask_Move_WithTargetData.h"
#include "Character/DCharacter.h"

#include "AbilitySystemComponent.h"

UDAbilityTask_Move_WithTargetData::UDAbilityTask_Move_WithTargetData()
{
	TargetClass = AGameplayAbilityTargetActor::StaticClass();
	TargetActor = nullptr;
	ConfirmationType = EGameplayTargetingConfirmation::UserConfirmed;
	Caster = nullptr;
}

UDAbilityTask_Move_WithTargetData* UDAbilityTask_Move_WithTargetData::CreateTask(UGameplayAbility* OwningAbility)
{
	UDAbilityTask_Move_WithTargetData* MyObj = NewAbilityTask<UDAbilityTask_Move_WithTargetData>(OwningAbility, FName("Move"));

	MyObj->Ability = OwningAbility;
	MyObj->AbilitySystemComponent = OwningAbility->GetAbilitySystemComponentFromActorInfo();
	MyObj->TaskOwner = OwningAbility;
	MyObj->Caster = Cast<ADCharacter>(MyObj->AbilitySystemComponent->GetOwnerActor());
	
	return MyObj;
}

void UDAbilityTask_Move_WithTargetData::Activate()
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
