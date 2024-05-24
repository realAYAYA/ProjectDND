// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "NavigationSystem.h"
#include "TurnBasedBattleInstance.h"
#include "Character/DCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Net/UnrealNetwork.h"


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

void ADPlayerController::PostNetInit()
{
	Super::PostNetInit();

	// Todo 向主机提交一分自己的用户信息，主机收到后会将新玩家信息转发到其它客户端
	ClientSendPlayerInfo();
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

bool ADPlayerController::InBattle() const
{
	if (const auto* DCharacter = Cast<ADCharacter>(GetPawn()))
		return DCharacter->InBattle();

	return false;
}

void ADPlayerController::K2_TurnEnd()
{
	const auto* DCharacter = Cast<ADCharacter>(this->GetPawn());
	if (!DCharacter || !DCharacter->IsMyTurn())
	{
		return;// 检查当前是否为自己回合
	}
	
	Server_TurnEnd();
}

void ADPlayerController::Client_MyTurn(const ADCharacter* InCharacter)
{
	K2_YourTurn(InCharacter);
}

void ADPlayerController::Server_TurnEnd_Implementation()
{
	auto* DCharacter = Cast<ADCharacter>(this->GetPawn());
	if (DCharacter && DCharacter->BattleInstance)
	{
		DCharacter->bReadyTurnEnd = true;
		DCharacter->BattleInstance->TurnEnd(DCharacter);
	}
}

void ADPlayerController::ClientSendPlayerInfo_Implementation()
{
}

void ADPlayerController::ServerSendPlayerInfo_Implementation()
{
	ServerSendPlayerInfo();// 服务器向其它所有客户端广播
}

void ADPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADPlayerController, PlayerId, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}