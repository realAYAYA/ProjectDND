#pragma once

#include "CoreMinimal.h"
#include "InventoryBase.h"
#include "GameFramework/SaveGame.h"
#include "DGameTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectD, Log, All);

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
struct FDGameSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "ProjectD")
	float TotalAudioVolume = 1;
	
};

USTRUCT(BlueprintType)
struct FDRoleInventoryData
{
	GENERATED_USTRUCT_BODY()

	// 仓库中的道具
	UPROPERTY()
	TArray<FInventoryItemBase> ItemsInStore;

	// 角色身上的道具，装备、背包、口袋、背心
	UPROPERTY()
	TArray<FInventoryItemBase> ItemsOnRole;
};

USTRUCT(BlueprintType)
struct FDRoleData
{
	GENERATED_USTRUCT_BODY()

	// 背包数据
	UPROPERTY()
	FDRoleInventoryData InventoryData;
	
	// 商店数据
	// 技能数据
	// 外观数据
	// 副职业数据 例如烹饪，工程，炼金，
};

USTRUCT(BlueprintType)
struct FDGameSaveData
{
	GENERATED_USTRUCT_BODY()

	// Steam Ps4 Xbox
	UPROPERTY()
	int64 PlayerId = 0;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FString PlatformId;// SteamId | PS4 | Xbox ...
};

USTRUCT(BlueprintType)
struct FDGameAchievements
{
	GENERATED_USTRUCT_BODY()
};