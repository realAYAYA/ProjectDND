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

	FDInventoryItem* GetItem();
	int32 GetItemIndex();
	
	
	UPROPERTY()
	TArray<FDInventoryItem>	Items_Internal;

	UPROPERTY()
	UDInventoryComponent* Owner = nullptr;

	/*//增加元素
	int index = Items.Add(FExampleItemEntry());
	MarkItemDirty(Items[index]);
	//修改元素
	Items[index].ExampleIntProperty = NewExampleIntProperty;
	MarkItemDirty(Items[index]);
	//删除元素
	Items.RemoveAt(index);
	MarkArrayDirty();*/
};

template<>
struct TStructOpsTypeTraits<FDInventoryItemsContainer> : public TStructOpsTypeTraitsBase2<FDInventoryItemsContainer>
{
	enum { WithNetDeltaSerializer = true };
};


UCLASS()
class UDInventoryComponent : public UObject, public FInventoryBase
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;
	
};