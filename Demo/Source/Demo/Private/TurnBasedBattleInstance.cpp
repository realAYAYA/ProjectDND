// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"

#include "DCharacterManager.h"
#include "DGameInstance.h"
#include "DPlayerController.h"
#include "Character/DCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATurnBasedBattleInstance::ATurnBasedBattleInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	CurrentCharacter = nullptr;
}

void ATurnBasedBattleInstance::K2_BuildBattleQueue_Implementation(const TArray<int64>& CharacterIds)
{
	if (GetNetMode() == NM_Client)
		return;

	const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance());
	if (!GameInstance)
		return;
	
	for (const auto Id : CharacterIds)
	{
		if (const auto* Character = GameInstance->CharacterManager->Find(Id))
		{
			if (auto* PC = Cast<ADPlayerController>(Character->GetPlayerState()->GetPlayerController()))
			{
				PC->GetInBattle(this);
				CharacterIdList.Add(Id);
			}
		}
	}

	// Todo
	// 计算先攻顺序
	// 通知第一个角色调用YourTurn
	if (CharacterIdList.IsValidIndex(0))
	{
		auto* Character = GameInstance->CharacterManager->Find(CharacterIdList[0]);
		if (Character && Character->BattleInstance == this)
		{
			YourTurn(Character);
		}
	}
}

// Called when the game starts or when spawned
void ATurnBasedBattleInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnBasedBattleInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnBasedBattleInstance::ReqTurnEnd(const ADCharacter* InCharacter)
{
	// 当前回合角色不符合
	if (CurrentCharacter != InCharacter)
		return;
	
	// 切换下一个角色
	const int64 Id = InCharacter->GetRoleId();
	int32 Index = CharacterIdList.Find(Id) + 1;
	if (!CharacterIdList.IsValidIndex(Index))
		Index = 0;

	if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
	{
		auto* Character = GameInstance->CharacterManager->Find(CharacterIdList[Index]);
		if (Character && Character->BattleInstance == this)
		{
			YourTurn(Character);
		}
	}
}

void ATurnBasedBattleInstance::YourTurn(ADCharacter* InCharacter)
{
	CurrentCharacter = InCharacter;
	InCharacter->YourTurn();
}

void ATurnBasedBattleInstance::OnCurrentCharacterChange()
{
}

void ATurnBasedBattleInstance::OnCharacterListChange()
{
}

void ATurnBasedBattleInstance::OnTurnNumChanged()
{
	
}

void ATurnBasedBattleInstance::MergeBattle(ATurnBasedBattleInstance* In)
{
}

void ATurnBasedBattleInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CurrentTurnNum, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CharacterIdList, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ATurnBasedBattleInstance, CurrentCharacter, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

