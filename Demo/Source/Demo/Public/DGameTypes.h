#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "GameFramework/SaveGame.h"

#include "InventoryBase.h"
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FDInventoryItemsContainer;

/*
	三个函数只有客户端才能调用
	void PreReplicatedRemove(const FDInventoryItemsContainer &InArray);
	void PostReplicatedAdd(const FDInventoryItemsContainer &InArray);
	void PostReplicatedChange(const FDInventoryItemsContainer &InArray);
	如果一个元素是被删除，之后又添加了新的，不一定会调PreReplicatedRemove()以及PostReplicatedAdd()，有可能只有一个PostReplicatedChange()
*/

USTRUCT(BlueprintType)
struct FDInventoryItem : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()
	
	void PreReplicatedRemove(const FDInventoryItemsContainer &InArray);
	void PostReplicatedAdd(const FDInventoryItemsContainer &InArray);
	void PostReplicatedChange(const FDInventoryItemsContainer &InArray);

	FDInventoryItem& operator=(const FInventoryItemBase& Other): BaseData(Other)
	{
		return *this;
	}

	int64 Uid() const { return BaseData.Uid; }
	void SetUid(const int64 Id) { BaseData.Uid = Id; }

	UPROPERTY()
	FInventoryItemBase BaseData;
};

USTRUCT()
struct FDInventoryItemsContainer : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY();

	FDInventoryItemsContainer()
	{
		
	}
	
	explicit FDInventoryItemsContainer(UDInventoryComponent* Owner): Owner(Owner)
	{
		
	}

	void SetOwner(UDInventoryComponent* InOwner);
	
	void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FDInventoryItem, FDInventoryItemsContainer>( Items_Internal, DeltaParams, *this );
	}

	FDInventoryItem* Add();
	void Add(const FDInventoryItem& InItem);

	void Remove(const FDInventoryItem* Item);
	void RemoveWithIndex(const int32 Index);

	FDInventoryItem* GetItem(const int32 Id);
	int32 GetItemIndex(const FDInventoryItem* Item);
	int32 GetItemIndexWithId(const int32 Id);
	
	UPROPERTY()
	TArray<FDInventoryItem>	Items_Internal;

	UPROPERTY()
	UDInventoryComponent* Owner = nullptr;

	UPROPERTY()
	int64 SerialId = 0;
};

template<>
struct TStructOpsTypeTraits<FDInventoryItemsContainer> : public TStructOpsTypeTraitsBase2<FDInventoryItemsContainer>
{
	enum { WithNetDeltaSerializer = true };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 装备所处容器
UENUM()
enum EDContainerType
{
	None,
	Pocket,
	Vest,
	Backpack,
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