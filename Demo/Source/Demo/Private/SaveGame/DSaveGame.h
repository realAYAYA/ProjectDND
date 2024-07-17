#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DSaveGame.generated.h"

/*
 * SaveGame Slot命名规则
 * SteamId
 */
UCLASS()
class UDSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	// SteamId
	UPROPERTY(BlueprintReadWrite, Category = "ProjectD")
	int32 UserId = 0;

	UPROPERTY(BlueprintReadWrite, Category = "ProjectD")
	bool bFirstGame = false;

	UPROPERTY(BlueprintReadWrite, Category = "ProjectD")
	bool bSkipTutorial = false;
};
