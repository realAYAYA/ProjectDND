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

UDInventoryComponent::UDInventoryComponent()
{
	SetIsReplicated(true);
}

void UDInventoryComponent::LoadData(const FDRoleInventoryData& InData)
{
	// 初始化容器布局配置Id，来自角色及其装备上提供的配置
	VestId = PocketId = BackPackId = 0;
	Layout_Vest;
	Layout_Pocket;
	Layout_BackPack;

	// 初始化空间布局
	{
		FDContainerLayout* Layout = &Layout_Pocket;

		Layout->Spaces.Empty();
		Layout->Spaces.Init(FIntArray2D(), Layout->Layouts.Num());
		
		for (int32 i = 0; i < Layout->Layouts.Num(); i++)
		{
			Layout->Spaces[i].Init(Layout->Layouts[i].X, Layout->Layouts[i].Y);
		}
	}

	// 接着尝试将背包数据中的道具一个个塞进各自容器中，可能存在非法数据，或配置变更导致道具无法塞进原在的空间中，因此需要鉴定并特殊处理（邮件补发）
	for (const auto& Item : InData.ItemsOnRole)
	{
		EDContainerType Container = static_cast<EDContainerType>(Item.Position.Z);

		// 选中容器
		FDContainerLayout* Layout;
		switch (Container)
		{
			default: Layout = nullptr; break;
		case EDContainerType::Pocket: Layout = &Layout_Pocket;break;
		case EDContainerType::Vest: Layout = &Layout_Vest;break;
		case EDContainerType::Backpack: Layout = &Layout_BackPack;break;
		}

		FIntVector2 Size(1, 1);
		FIntVector2 Pos(Item.Position.X, Item.Position.Y);
		int32 SlotIndex = Item.Position.W;
		
		// CanAddItem(Layout, Pos, Size, Slot)
		{
			
		}
	}
}


void UDInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDInventoryComponent, ItemArray, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
