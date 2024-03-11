// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "TurnBasedBattleInstance.h"
#include "Character/DCharacter.h"

void ADPlayerController::K2_TurnEnd()
{
	// 当前并不是自己的回合
	if (const auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		if (DCharacter->BattleInstance->CurrentCharacter != DCharacter)
			return;
	}
	
	ReqTurnEnd();
}

void ADPlayerController::OnBattle_Implementation(const ADCharacter* InCharacter)
{
	K2_OnBattle(InCharacter);
}

void ADPlayerController::GetInBattle(ATurnBasedBattleInstance* BattleInstance)
{
	if (auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		DCharacter->SetBattleInstance(BattleInstance);
		OnBattle(DCharacter);
	}
}

void ADPlayerController::BattleEnd_Implementation()
{
	BattleEnd();
}

void ADPlayerController::YourTurn_Implementation(const ADCharacter* InCharacter)
{
	K2_YourTurn(InCharacter);
}

void ADPlayerController::ReqTurnEnd_Implementation()
{
	if (const auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		DCharacter->BattleInstance->ReqTurnEnd(DCharacter);
	}
}
