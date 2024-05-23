// Fill out your copyright notice in the Description page of Project Settings.


#include "DBlueprintFunctionLibrary.h"

#include "DGameInstance.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

UDGameInstance* UDBlueprintFunctionLibrary::GetDGameInstance(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World ? Cast<UDGameInstance>(World->GetGameInstance()) : nullptr;
}

UNavigationPath* UDBlueprintFunctionLibrary::FindPath(AController* Controller, const FVector& GoalLocation)
{
	UNavigationSystemV1* NavSys = Controller ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld()) : nullptr;
	if (NavSys == nullptr || Controller == nullptr || Controller->GetPawn() == nullptr)
	{
		return nullptr;
	}

	const UPathFollowingComponent* PFollowComp = Controller->FindComponentByClass<UPathFollowingComponent>();

	if (PFollowComp == nullptr)
	{
		return nullptr;
	}

	if (!PFollowComp->IsPathFollowingAllowed())
	{
		return nullptr;
	}

	const bool bAlreadyAtGoal = PFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);
	if (!bAlreadyAtGoal)
	{
		const FVector AgentNavLocation = Controller->GetNavAgentLocation();
		if (const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef(), AgentNavLocation))
		{
			const FPathFindingQuery Query(Controller, *NavData, AgentNavLocation, GoalLocation);
			const FPathFindingResult Result = NavSys->FindPathSync(Query);
			if (Result.IsSuccessful())
			{
				UNavigationPath* ResultPath = NewObject<UNavigationPath>();
				ResultPath->SetPath(Result.Path);
				return ResultPath;
			}
		}
	}
	
	return nullptr;
}
