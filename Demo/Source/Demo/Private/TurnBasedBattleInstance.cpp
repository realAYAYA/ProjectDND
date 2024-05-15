// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"
#include "DCharacterManager.h"
#include "DGameInstance.h"
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
	CurrentCharacter = nullptr;
}

// Called when the game starts or when spawned
void ATurnBasedBattleInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnBasedBattleInstance::PostNetInit()
{
	Super::PostNetInit();

	if (CurrentCharacter)
		CurrentCharacter->YourTurn();

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

void ATurnBasedBattleInstance::SetCurrentCharacter(ADCharacter* In)
{
	CurrentCharacter = In;
	
#if !UE_SERVER
	if (HasAuthority())
		OnRep_CurrentCharacter();// 如果不是DS，但作为主机端，需要单独执行表现
#endif
}

void ATurnBasedBattleInstance::BeginBattle()
{
	if (!HasAuthority())
		return;

	const UDGameplayEffect* GameplayEffect = BattleBeginGEClass->GetDefaultObject<UDGameplayEffect>();
	for (const auto* Character : CharacterList)
	{
		const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_BattleBegin;
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Character->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);

		Character->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectToSelf(GameplayEffect, 0, 0, FGameplayEffectContextHandle());
	}
	
	// Todo
	// 计算先攻顺序, 通知第一个角色调用YourTurn
	if (CharacterList.IsValidIndex(0))
	{
		if (auto* NextCharacter = CharacterList[0]; NextCharacter && NextCharacter->BattleInstance == this)
		{
			YourTurn(NextCharacter);
		}
	}
}

void ATurnBasedBattleInstance::TurnEnd(const ADCharacter* InCharacter)
{
	// 当前回合角色不符合
	if (!CurrentCharacter || CurrentCharacter != InCharacter)
		return;
	
	// 切换下一个角色
	ADCharacter* FoundCharacter = nullptr;
	int32 Index = FindCharacter(InCharacter->GetRoleId(), FoundCharacter) + 1;
	if (!CharacterList.IsValidIndex(Index))
		Index = 0;

	if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
	{
		auto* NextCharacter = GameInstance->CharacterManager->Find(CharacterList[Index]->GetRoleId());
		if (NextCharacter && NextCharacter->BattleInstance == this)
		{
			YourTurn(NextCharacter);
		}
	}
}

void ATurnBasedBattleInstance::YourTurn(ADCharacter* InCharacter)
{
	SetCurrentCharacter(InCharacter);

	const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_MyTurn;
	FGameplayEventData Payload;
	Payload.EventTag = Tag;
	InCharacter->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	
	// Todo 恢复动作 移动力 附赠动作
	const UDGameplayEffect* GameplayEffect = MyTurnGEClass->GetDefaultObject<UDGameplayEffect>();
	InCharacter->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectToSelf(GameplayEffect, 0, 0, FGameplayEffectContextHandle());
}

void ATurnBasedBattleInstance::OnRep_CurrentCharacter()
{
	if (CurrentCharacter)
		CurrentCharacter->YourTurn();
}

void ATurnBasedBattleInstance::OnRep_CharacterList()
{
}

void ATurnBasedBattleInstance::OnTurnNumChanged()
{
	
}

void ATurnBasedBattleInstance::MergeBattle(ATurnBasedBattleInstance* In)
{
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
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CurrentTurnNum, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CurrentCharacter, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

