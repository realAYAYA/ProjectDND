// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"
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
		if (Character)
		{
			Character->OnBattleBegin(this);
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

	ActivatedCharacters.Empty();
	
	CurrentTurnInfo.CurrentTurnNum = 1;
	CurrentTurnInfo.CurrentIndex = 0;
	
	// Todo
	// 计算先攻顺序, 通知第一个角色调用YourTurn
	if (CharacterList.IsValidIndex(0))
	{
		if (auto* NextCharacter = CharacterList[0])
		{
			ActivatedCharacters.Add(NextCharacter);
			YourTurn(NextCharacter);
		}
	}

#if !UE_SERVER
	if (HasAuthority())
		OnTurnChanged();
#endif
}

void ATurnBasedBattleInstance::TurnEnd(const ADCharacter* InCharacter)
{
	// 不是该角色的回合
	if (!IsMyTurn(InCharacter))
		return;

	// 检查所有可活动的角色是否同时结束回合
	for (const auto* Character : ActivatedCharacters)
	{
		if (Character && !Character->bReadyTurnEnd)
		{
			return;
		}
	}
	
	// 切换下一回合角色
	ActivatedCharacters.Empty();
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

#if !UE_SERVER
	if (HasAuthority())
		OnTurnChanged();
#endif
	
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
	
	for (const auto* Character : ActivatedCharacters)
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
	
#if WITH_EDITOR
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("服务器回合变更"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("客户端接收回合变更消息"));
	}
#endif
	
	if (CurrentTurnInfo.CurrentIndex == -1)
	{
		// Todo 战斗结束
	}
	
	// 通知角色及其PlayerController回合开始
	for (auto* Character : ActivatedCharacters)
	{
		Character->Client_MyTurn();
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
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CharacterList, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, ActivatedCharacters, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

