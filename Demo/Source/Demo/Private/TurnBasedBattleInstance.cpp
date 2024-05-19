// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"
#include "DPlayerController.h"
#include "Character/DCharacter.h"

#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATurnBasedBattleInstance::ATurnBasedBattleInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ATurnBasedBattleInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnBasedBattleInstance::PostNetInit()
{
	Super::PostNetInit();
	
	for (const auto& Character : CharacterList)
	{
		// 如果角色是本地控制的，通知其PlayerController进入战斗
		if (Character && Character->IsLocallyControlled())
		{
			if (auto* PC = Cast<ADPlayerController>(Character->Controller))
			{
				PC->K2_OnBattle(Character);// 通知用户进入战斗（战斗界面, 操作模式变更）
			}
		}
	}
}

// Called every frame
void ATurnBasedBattleInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnBasedBattleInstance::BeginBattle()
{
	if (!HasAuthority())
		return;
	
	for (const auto* Character : CharacterList)
	{
		const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_BattleBegin;
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Character->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}

	CurrentTurnInfo.ActivatedCharacters.Empty();
	
	CurrentTurnInfo.CurrentIndex = 1;
	
	// Todo
	// 计算先攻顺序, 通知第一个角色调用YourTurn
	if (CharacterList.IsValidIndex(0))
	{
		if (auto* NextCharacter = CharacterList[0]; NextCharacter && NextCharacter->BattleInstance == this)
		{
			CurrentTurnInfo.ActivatedCharacters.Add(NextCharacter);
			YourTurn(NextCharacter);
		}
	}
}

void ATurnBasedBattleInstance::TurnEnd(const ADCharacter* InCharacter)
{
	// Todo 压根不是该角色的回合

	// 检查所有可活动的角色是否同时结束回合
	for (const auto* Character : CurrentTurnInfo.ActivatedCharacters)
	{
		if (Character && !Character->bReadyTurnEnd)
		{
			return;
		}
	}
	
	// 切换下一回合角色
	CurrentTurnInfo.ActivatedCharacters.Empty();
	for (int32 i = CurrentTurnInfo.CurrentIndex + 1; i < CharacterList.Num(); i++)
	{
		// Todo 可能不止一个，如果队列中连续几个角色阵营相同，则允许这些角色同时进入回合
	}
	
	{
		if (const auto* Character = CharacterList[CurrentTurnInfo.CurrentIndex + 1])
		{
			YourTurn(Character);
			CurrentTurnInfo.CurrentIndex += 1;
		}
	}

	CurrentTurnInfo.CurrentTurnNum += 1;// 回合数+1
}

void ATurnBasedBattleInstance::YourTurn(const ADCharacter* InCharacter)
{
	const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_MyTurn;
	FGameplayEventData Payload;
	Payload.EventTag = Tag;
	InCharacter->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
}

bool ATurnBasedBattleInstance::IsMyTurn(const ADCharacter* InCharacter) const
{
	if (!InCharacter)
		return false;
	
	for (const auto* Character : CurrentTurnInfo.ActivatedCharacters)
	{
		if (Character->GetRoleId() == InCharacter->GetRoleId())
			return true;
	}

	return false;
}

void ATurnBasedBattleInstance::SomeoneDied(const ADCharacter* InCharacter)
{
	// Todo 检查数据，是否结束战斗
}


void ATurnBasedBattleInstance::OnRep_CharacterList()
{
	// Todo 有新角色加入战斗，通常新加入战斗的角色先攻掷点不会在当前回合角色之前
}

void ATurnBasedBattleInstance::OnTurnChanged()
{
	if (CurrentTurnInfo.CurrentIndex == -1)
	{
		// Todo 战斗结束
	}
	
	// 通知角色及其PlayerController回合开始
	for (auto* Character : CurrentTurnInfo.ActivatedCharacters)
	{
		Character->MyTurn();
	}
}

void ATurnBasedBattleInstance::MergeBattle(ATurnBasedBattleInstance* In)
{
	// Todo 合并两场战斗
}

int32 ATurnBasedBattleInstance::FindCharacter(const int32 Id, ADCharacter*& Out) const
{
	for (int32 i = 0; i < CharacterList.Num(); i++)
	{
		if (CharacterList[i]->GetRoleId() == Id)
		{
			Out = CharacterList[i];
			return i;
		}
	}

	return INDEX_NONE;
}

void ATurnBasedBattleInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CurrentTurnInfo, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

