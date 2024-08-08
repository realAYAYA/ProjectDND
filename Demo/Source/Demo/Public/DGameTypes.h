#pragma once

#include "CoreMinimal.h"
#include "InventoryBase.h"
#include "Net/Serialization/FastArraySerializer.h"

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


// 装备所处容器
UENUM()
enum EDContainerType
{
	None,
	Pocket,
	Vest,
	Backpack,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FDInventoryItemsContainer;
struct FDInventoryItem;

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

	void AddNum(const int32 InNum, const bool bOverwrite = false)
	{
		if (bOverwrite)
			ItemData.Num = InNum;
		else
		{
			ItemData.Num += InNum;
		}
	}
	int32 Num() const { return ItemData.Num; }

	FIntVector2 GetPos() const { return FIntVector2(ItemData.Position.X, ItemData.Position.Y); }
	void SetPos(const FIntVector2 Pos)
	{
		ItemData.Position.X = Pos.X;
		ItemData.Position.Y = Pos.Y;
	}

	int32 GetSlot() const { return ItemData.Position.W; }
	void SetSlot(const int32 Slot) { ItemData.Position.W = Slot; }

	EDContainerType GetContainer() const { return static_cast<EDContainerType>(ItemData.Position.Z); }
	void SetContainer(const EDContainerType In) { ItemData.Position.Z = static_cast<int32>(In); }
	
	int32 GetContainerId() const { return ItemData.Position.Z; }
	void SetContainerId(const int32 Id) { ItemData.Position.Z = Id; }

	int32 Uid() const { return ItemData.Uid; }
	void SetUid(const int32 Id) { ItemData.Uid = Id; }

	int32 CfgId() const { return ItemData.ConfigId; }
	void SetCfgId(const int32 Id) { ItemData.ConfigId = Id; }
	
	UPROPERTY(BlueprintReadOnly)
	FInventoryItemBase ItemData;// 实际道具数据

	FDInventoryItemsContainer* Container;
};


// Todo 设计：背包系统支持在“背包或口袋或背心中装入其它容器，但除此之外的容器之前不允许套娃！

class UDInventoryComponent;

USTRUCT()
struct FDInventoryItemsContainer : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY();

	FDInventoryItemsContainer()
	{
		
	}
	
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

	const FDInventoryItem* GetItem(const int32 Id) const;
	FDInventoryItem* GetItem(const int32 Id);
	int32 GetItemIndex(const FDInventoryItem* Item);
	int32 GetItemIndexWithId(const int32 Id);
	
	UPROPERTY()
	TArray<FDInventoryItem>	Items_Internal;

	UPROPERTY()
	UDInventoryComponent* Owner = nullptr;

	UPROPERTY()
	int32 SerialId = 0;

	int32 GenerateItemId()
	{
		if (Items_Internal.Num() == 0)
			SerialId = 100;
		return ++SerialId;
	}
};

template<>
struct TStructOpsTypeTraits<FDInventoryItemsContainer> : public TStructOpsTypeTraitsBase2<FDInventoryItemsContainer>
{
	enum { WithNetDeltaSerializer = true };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


USTRUCT(BlueprintType)
struct FDRoleInventoryData
{
	GENERATED_USTRUCT_BODY()

	// 仓库中的道具
	UPROPERTY()
	TArray<FDInventoryItem> ItemsInStore;

	// 角色身上的道具，装备、背包、口袋、背心
	UPROPERTY()
	TArray<FDInventoryItem> ItemsOnRole;

	UPROPERTY()
	int32 PocketId = 0;
	
	UPROPERTY()
	int32 VestId = 0;
	
	UPROPERTY()
	int32 BackPackId = 0;
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