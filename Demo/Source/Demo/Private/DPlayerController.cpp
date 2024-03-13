// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "NavigationSystem.h"
#include "TurnBasedBattleInstance.h"
#include "Character/DCharacter.h"
#include "Navigation/PathFollowingComponent.h"


ADPlayerController::ADPlayerController(const FObjectInitializer& ObjectInitializer)
{
	PathFollowingComponent = CreateOptionalDefaultSubobject<UPathFollowingComponent>(TEXT("PathFollowingComponent"));
	if (PathFollowingComponent)
	{
		//PathFollowingComponent->OnRequestFinished.AddUObject(this, &ADPlayerController::OnMoveCompleted);
	}
}

void ADPlayerController::Reset()
{
	Super::Reset();

	if (PathFollowingComponent)
	{
		PathFollowingComponent->AbortMove(*this, FPathFollowingResultFlags::OwnerFinished | FPathFollowingResultFlags::ForcedScript);
	}
}

void ADPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// not calling UpdateNavigationComponents() anymore. The PathFollowingComponent 
	// is now observing newly possessed pawns (via OnNewPawn)

	if (PathFollowingComponent)
	{
		PathFollowingComponent->Initialize();
	}
}

void ADPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (PathFollowingComponent)
	{
		PathFollowingComponent->Cleanup();
	}
}

void ADPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	if (PathFollowingComponent)
	{
		PathFollowingComponent->Initialize();
	}
}

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
