// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedBattleInstance.h"

#include "DPlayerController.h"
#include "Character/DCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATurnBasedBattleInstance::ATurnBasedBattleInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	CurrentCharacter = nullptr;
}

void ATurnBasedBattleInstance::K2_BuildBattleQueue_Implementation(const TArray<ADCharacter*>& InCharacters)
{
	/*if (UKismetSystemLibrary::IsServer(this))
	{
		
	}*/

	CharacterList = InCharacters;
	for (const auto* Character : CharacterList)
	{
		if (auto* PC = Cast<ADPlayerController>(Character->GetPlayerState()->GetPlayerController()))
		{
			PC->GetInBattle(this);
		}
	}

	// Todo
	// 计算先攻顺序
	// 通知第一个角色调用YourTurn
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
	// 角色结束回合
	// 切换下一个角色
}

void ATurnBasedBattleInstance::YourTurn(const ADCharacter* InCharacter)
{
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

	
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

