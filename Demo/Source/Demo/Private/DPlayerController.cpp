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

bool ADPlayerController::MoveTo(const FVector& GoalLocation) const
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this->GetWorld());
	if (NavSys == nullptr || this->GetPawn() == nullptr)
	{
		return false;
	}

	UPathFollowingComponent* PFollowComp = this->PathFollowingComponent.Get();

	if (PFollowComp == nullptr)
	{
		return false;
	}

	if (!PFollowComp->IsPathFollowingAllowed())
	{
		return false;
	}

	const bool bAlreadyAtGoal = PFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest, bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);

		return false;
	}

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);

		return false;
	}

	if (bAlreadyAtGoal)
	{
		PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
		return false;
	}
	else
	{
		const FVector AgentNavLocation = GetNavAgentLocation();
		if (const ANavigationData* NavData = NavSys->GetNavDataForProps(GetNavAgentPropertiesRef(), AgentNavLocation))
		{
			const FPathFindingQuery Query(this, *NavData, AgentNavLocation, GoalLocation);
			const FPathFindingResult Result = NavSys->FindPathSync(Query);
			if (Result.IsSuccessful())
			{
				PFollowComp->RequestMove(FAIMoveRequest(GoalLocation), Result.Path);
			}
			else if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
				return false;
			}
		}
	}

	return true;
}

void ADPlayerController::StopMove() const
{
	const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this->GetWorld());
	if (NavSys == nullptr || this->GetPawn() == nullptr)
	{
		return;
	}
	
	PathFollowingComponent->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::MovementStop);
}

void ADPlayerController::K2_TurnEnd()
{
	// 当前并不是自己的回合
	if (const auto* DCharacter = Cast<ADCharacter>(this->GetPawn()))
	{
		if (DCharacter->BattleInstance && DCharacter->BattleInstance->CurrentCharacter != DCharacter)
			return;
	}
	
	ReqTurnEnd();
}


void ADPlayerController::YourTurn_Implementation(const ADCharacter* InCharacter)
{
	K2_YourTurn(InCharacter);
}

void ADPlayerController::ReqTurnEnd_Implementation()
{
	const auto* DCharacter = Cast<ADCharacter>(this->GetPawn());
	if (DCharacter && DCharacter->BattleInstance)
	{
		DCharacter->BattleInstance->TurnEnd(DCharacter);
	}
}
