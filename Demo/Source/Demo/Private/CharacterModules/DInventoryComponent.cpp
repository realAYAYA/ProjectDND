#include "D:\Codes\54\UnrealEngine\Engine\Intermediate\Build\Win64\x64\UnrealEditorGPF\Development\UnrealEd\SharedPCH.UnrealEd.Project.ValApi.Cpp20.h"
#include "DInventoryComponent.h"

void FDInventoryItem::PreReplicatedRemove(const FDInventoryItemsContainer& InArray)
{
}

void FDInventoryItem::PostReplicatedAdd(const FDInventoryItemsContainer& InArray)
{
}

void FDInventoryItem::PostReplicatedChange(const FDInventoryItemsContainer& InArray)
{
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
	return nullptr;
}

void FDInventoryItemsContainer::Remove(FDInventoryItem* Item)
{
}

void FDInventoryItemsContainer::RemoveWithIndex(const int32 Index)
{
}

FDInventoryItem* FDInventoryItemsContainer::GetItem()
{
	return nullptr;
}

int32 FDInventoryItemsContainer::GetItemIndex()
{
	return 0;
}
