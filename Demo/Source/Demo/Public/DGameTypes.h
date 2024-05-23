#pragma once

#include "CoreMinimal.h"
#include "DGameTypes.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDCharacterGasData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
};

UCLASS()
class UDCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	FDCharacterGasData GasData;
};

USTRUCT(BlueprintType)
struct FDPlayerData
{
	GENERATED_USTRUCT_BODY()

	// Steam Ps4 Xbox
	UPROPERTY()
	uint64 PlayerId = 0;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FString PlatformId;// SteamId | PS4 | Xbox ...
};