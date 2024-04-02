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
	}
	
	EndTask();
}
