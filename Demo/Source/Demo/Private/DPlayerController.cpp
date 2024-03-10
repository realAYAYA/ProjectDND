// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "Character/DCharacter.h"

void ADPlayerController::K2_TurnEnd()
{
}

void ADPlayerController::NotifyOnBattle_Implementation()
{
	ClientOnBattle();
	
}

void ADPlayerController::GetInBattle(ATurnBasedBattleInstance* BattleInstance)
{
	if (auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		DCharacter->SetBattleInstance(BattleInstance);
		NotifyOnBattle();
	}
}

void ADPlayerController::BattleEnd_Implementation()
{
}

void ADPlayerController::NotifyYourTurn_Implementation(const ADCharacter* InCharacter)
{
	
}

void ADPlayerController::YourTurn(const ADCharacter* InCharacter)
{
	NotifyYourTurn(InCharacter);
}

void ADPlayerController::ReqTurnEnd_Implementation()
{
	if (auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		DCharacter->ReqTurnEnd();
	}
}
