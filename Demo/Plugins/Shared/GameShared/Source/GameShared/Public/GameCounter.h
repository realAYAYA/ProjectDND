#pragma once
#include "CoreMinimal.h"
#include "GameCounter.generated.h"

// 计数器层级1
USTRUCT(BlueprintType)
struct GAMESHARED_API FCounterLayer1
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, int64> Map;
};

// 计数器层级2
USTRUCT(BlueprintType)
struct GAMESHARED_API FCounterLayer2
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, FCounterLayer1> Map;
};

// 计数器层级3
USTRUCT(BlueprintType)
struct GAMESHARED_API FCounterLayer3
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<int32, FCounterLayer3> Map;
};