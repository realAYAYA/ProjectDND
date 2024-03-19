// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_Move.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GameplayAbilitySystem/TargetData/DTargetActor.h"

UAbilityTask_Move::UAbilityTask_Move()
{
	TargetClass = ADTargetActor::StaticClass();
	TargetActor = nullptr;
	ConfirmationType = EGameplayTargetingConfirmation::UserConfirmed;
	Caster = nullptr;
}

UAbilityTask_Move* UAbilityTask_Move::CreateMoveTask(UGameplayAbility* OwningAbility, ADCharacter* Character)
{
	UAbilityTask_Move* MyObj = NewAbilityTask<UAbilityTask_Move>(OwningAbility, FName("Move"));

	MyObj->Caster = Character;
	
	return MyObj;
}

void UAbilityTask_Move::Activate()
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

	OnAbilityCancel.Broadcast();
	EndTask();
}

void UAbilityTask_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (Caster && Caster->GetAttributeSet())
	{
		const auto* Att = Caster->GetAttributeSet();
		if (Att->GetMoveDistance() > 0)
			return;
	}

	OnAbilityTaskEnd.Broadcast();
	EndTask();
}
