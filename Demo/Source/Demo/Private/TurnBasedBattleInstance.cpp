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

	for (const auto& Id : CharacterIdList)
	{
		// 如果角色是本地控制的，通知其PlayerControler进入战斗
		ADCharacter* Character = nullptr;
		if (Character && Character->IsLocallyControlled())
		{
			if (auto* PC = Cast<ADPlayerController>(Character->Controller))
			{
				PC->K2_OnBattle(Character);
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

	const UDGameplayEffect* GameplayEffect = BattleBeginGEClass->GetDefaultObject<UDGameplayEffect>();
	for (const auto* Character : CharacterList)
		Character->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectToSelf(GameplayEffect, 0, 0, FGameplayEffectContextHandle());

	for (auto* Character : CharacterList)
		Character->SetBattleInstance(this);
	
	// Todo
	// 计算先攻顺序, 通知第一个角色调用YourTurn
	if (CharacterIdList.IsValidIndex(0))
	{
		auto* NextCharacter = FindCharacter(CharacterIdList[0]);
		if (NextCharacter && NextCharacter->BattleInstance == this)
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
	const int64 Id = InCharacter->GetRoleId();
	int32 Index = CharacterIdList.Find(Id) + 1;
	if (!CharacterIdList.IsValidIndex(Index))
		Index = 0;

	if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
	{
		auto* NextCharacter = GameInstance->CharacterManager->Find(CharacterIdList[Index]);
		if (NextCharacter && NextCharacter->BattleInstance == this)
		{
			YourTurn(NextCharacter);
		}
	}
}

void ATurnBasedBattleInstance::YourTurn(ADCharacter* InCharacter)
{
	CurrentCharacter = InCharacter;
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

ADCharacter* ATurnBasedBattleInstance::FindCharacter(const int32 Id) const
{
	for (auto* Character : CharacterList)
		if (Character->GetRoleId() == Id)
			return Character;

	return nullptr;
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

