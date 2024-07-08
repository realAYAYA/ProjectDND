#include "DInventoryComponent.h"

#include "Net/UnrealNetwork.h"

void FDInventoryItem::PreReplicatedRemove(const FDInventoryItemsContainer& InArray)
{
}

void FDInventoryItem::PostReplicatedAdd(const FDInventoryItemsContainer& InArray)
{
}

void FDInventoryItem::PostReplicatedChange(const FDInventoryItemsContainer& InArray)
{
	
}

void FDInventoryItemsContainer::SetOwner(UDInventoryComponent* InOwner)
{
	this->Owner = InOwner;
}

void FDInventoryItemsContainer::PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize)
{
}

void FDInventoryItemsContainer::PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize)
{
}

void FDInventoryItemsContainer::PostReplicatedChange(const TArrayView<int32>& ChangedIndices, int32 FinalSize)
{
}

FDInventoryItem* FDInventoryItemsContainer::Add()
{
	const int32 Index = Items_Internal.AddZeroed();
	MarkItemDirty(Items_Internal[Index]);
	return &Items_Internal[Index];
}

void FDInventoryItemsContainer::Remove(FDInventoryItem* Item)
{
	const int32 Index = GetItemIndex(Item);
	Items_Internal.RemoveAtSwap(Index);
	MarkArrayDirty();
}

void FDInventoryItemsContainer::RemoveWithIndex(const int32 Index)
{
	Items_Internal.RemoveAtSwap(Index);
	MarkArrayDirty();
}

FDInventoryItem* FDInventoryItemsContainer::GetItem(const int32 Id)
{
	for (int32 i = 0; i < Items_Internal.Num(); i++)
		if (Id == Items_Internal[i].Uid)
			return &Items_Internal[i];
	
	return nullptr;
}

int32 FDInventoryItemsContainer::GetItemIndex(const FDInventoryItem* Item)
{
	if (!Item)
		return INDEX_NONE;
	
	for (int32 i = 0; i < Items_Internal.Num(); i++)
		if (Item->Uid == Items_Internal[i].Uid)
			return i;
	
	return INDEX_NONE;
}

int32 FDInventoryItemsContainer::GetItemIndexWithId(const int32 Id)
{
	for (int32 i = 0; i < Items_Internal.Num(); i++)
		if (Id == Items_Internal[i].Uid)
			return i;
	
	return INDEX_NONE;
}


void UDInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDInventoryComponent, ItemArray, SharedParams);
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDInventoryComponent, ContainerSize, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
