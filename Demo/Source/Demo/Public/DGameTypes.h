#pragma once

#include "CoreMinimal.h"
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

	void AddNum(const int32 InNum, const bool bOverride = false)
	{
		if (bOverride)
			Num = InNum;
		else
		{
			Num += InNum;
		}
	}

	FIntVector2 GetPos() const { return FIntVector2(Position.X, Position.Y); }
	void SetPos(const FIntVector2 Pos)
	{
		Position.X = Pos.X;
		Position.Y = Pos.Y;
	}

	int32 GetSlot() const { return Position.W; }
	void SetSlot(const int32 Slot) { Position.W = Slot; }

	EDContainerType GetContainer() const { return static_cast<EDContainerType>(Position.Z); }
	void SetContainer(const EDContainerType Container) { Position.Z = static_cast<int32>(Container); }
	
	UPROPERTY(BlueprintReadOnly)
	int32 Uid = 0;
	
	// 堆叠数量
	UPROPERTY(BlueprintReadOnly)
	int64 Num = 0;

	// 生成日期
	UPROPERTY(BlueprintReadOnly)
	int64 BeginDate = 0;

	// 道具配置Id
	UPROPERTY(BlueprintReadOnly)
	int32 ConfigId = 0;

	// 背包中的位置，zw变量可根据需求解析，例如位于背心中的某个插槽
	UPROPERTY(BlueprintReadOnly)
	FIntVector4 Position;

	// 如果是容器则可能内含道具
	//UPROPERTY(BlueprintReadOnly)
	//TArray<FDInventoryItem> ItemsInContainer;

	// Todo Extensions 装备数据 强化 附魔
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
	int64 SerialId = 0;

	int32 GenerateItemId() { return ++SerialId; }
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