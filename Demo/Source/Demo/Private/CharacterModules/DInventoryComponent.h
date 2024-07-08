#pragma once
#include "CoreMinimal.h"
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
class UDInventoryComponent : public UObject, public FInventoryBase
{
	GENERATED_BODY()


	
	
protected:
	
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;

	// 容器布局，比如塔科夫的口袋就是4个'1x1'
	UPROPERTY(Replicated)
	TArray<FVector2D> ContainerSize;// 2 x 2

	// 容器配置Id，配置中可以含有更多表现相关的参数（比如决定UI的样式）
	UPROPERTY(Replicated);
	int32 ConfigId = 0;
};