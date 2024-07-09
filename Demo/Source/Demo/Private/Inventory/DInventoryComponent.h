#pragma once
#include "CoreMinimal.h"
#include "DGameTypes.h"
#include "InventoryBase.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "DInventoryComponent.generated.h"

class UDInventoryComponent;
struct FDInventoryItemsContainer;

/*
	三个函数只有客户端才能调用
	void PreReplicatedRemove(const FDInventoryItemsContainer &InArray);
	void PostReplicatedAdd(const FDInventoryItemsContainer &InArray);
	void PostReplicatedChange(const FDInventoryItemsContainer &InArray);
	如果一个元素是被删除，之后又添加了新的，不一定会调PreReplicatedRemove()以及PostReplicatedAdd()，有可能只有一个PostReplicatedChange()
*/

USTRUCT(BlueprintType)
struct FDInventoryItem : public FFastArraySerializerItem, public FInventoryItemBase
{
	GENERATED_USTRUCT_BODY()
	
	void PreReplicatedRemove(const FDInventoryItemsContainer &InArray);
	void PostReplicatedAdd(const FDInventoryItemsContainer &InArray);
	void PostReplicatedChange(const FDInventoryItemsContainer &InArray);
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

	void Remove(FDInventoryItem* Item);
	void RemoveWithIndex(const int32 Index);

	FDInventoryItem* GetItem(const int32 Id);
	int32 GetItemIndex(const FDInventoryItem* Item);
	int32 GetItemIndexWithId(const int32 Id);
	
	UPROPERTY()
	TArray<FDInventoryItem>	Items_Internal;

	UPROPERTY()
	UDInventoryComponent* Owner = nullptr;
};

template<>
struct TStructOpsTypeTraits<FDInventoryItemsContainer> : public TStructOpsTypeTraitsBase2<FDInventoryItemsContainer>
{
	enum { WithNetDeltaSerializer = true };
};


// 容器组件：口袋，背包，背心
UCLASS()
class UDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDInventoryComponent();

	// 移动道具，同一容器中移动，不同容器之间移动
	bool MoveItem(const int32 ItemId, const FVector2D NewPosition);
	
	// 穿装备 脱装备
	bool PutOn(const int32 ItemId, const int32 Slot);
	bool TakeOff(const int32 ItemId);
	
	void LoadData(const FDRoleInventoryData& InData);// Todo 如果有一天容器或道具属性配置被修改，如何检测，变为非法的道具或容器应作何处理
	void SaveData(FDRoleInventoryData* OutData);

	FDInventoryItem* GetItem(const int32 Id);

	int64 GetItemNumWithCfgId(const int32 CfgId) const;

	// 删除道具，根据数量不一定是移除道具
	void DeleteItem(const int32 Id, const int32 Num, const FString& Reason);
	void DeleteItemWithCfgId(const int32 CfgId, const int32 Num, const FString& Reason);

	bool AddItem(FDInventoryItem* Item, const FString& Reason);
	bool AddItemWithCfgId(const int32 CfgId, const int32 Num, const FString& Reason);

	void RemoveItem(const int32 Id);
	
protected:
	
	// 容器配置Id，配置中可以含有更多表现相关的参数（比如决定UI的样式）
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated);
	int32 VestId = 0;

	// 口袋容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated);
	int32 PocketId = 0;
	
	// 背包容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated);
	int32 BackPackId = 0;

	// 容器布局，比如塔科夫的口袋就是4个'1x1'
	TMap<int32, TArray<FVector2D>> ContainerLayout;

	// 装备栏位
	UPROPERTY(Replicated)
	FDInventoryItemsContainer Equipments;
	
	// 背心道具栏位
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray_Vest;
	
	// 口袋栏位
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray_Pocket;

	// 背包道具栏位
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray_BackPack;
};
