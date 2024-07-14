#include "DInventoryComponent.h"

#include "Net/UnrealNetwork.h"


UDInventoryComponent::UDInventoryComponent()
{
	SetIsReplicated(true);
}

void UDInventoryComponent::LoadData(const FDRoleInventoryData& InData)
{
	// Todo 如果有一天容器或道具属性配置被修改，如何检测，变为非法的道具或容器应作何处理
	
	// Todo 初始化容器布局配置Id，来自角色及其装备上提供的配置
	{
		VestId = InData.VestId;
		PocketId = InData.PocketId;
		BackPackId = InData.BackPackId;
		
		Layout_Vest;
		Layout_Pocket;
		Layout_BackPack;
	}

	// 初始化空间布局
	const auto Containers = {EDContainerType::Vest, EDContainerType::Vest, EDContainerType::Vest};
	for (const auto& Container : Containers)
	{
		FDContainerLayout* Layout = SwitchContainer(Container);

		Layout->Spaces.Empty();
		Layout->Spaces.Init(FIntArray2D(), Layout->Layouts.Num());
		
		for (int32 i = 0; i < Layout->Layouts.Num(); i++)
		{
			Layout->Spaces[i].Reset(Layout->Layouts[i].X, Layout->Layouts[i].Y);
		}
	}

	// 接着尝试将背包数据中的道具一个个塞进各自容器中，可能存在非法数据，或配置变更导致道具无法塞进原在的空间中，因此需要鉴定并特殊处理（邮件补发）
	for (const auto& Item : InData.ItemsOnRole)
	{
		const EDContainerType Container = static_cast<EDContainerType>(Item.Position.Z);

		// 选中容器
		FDContainerLayout* Layout = SwitchContainer(Container);
		
		FIntVector2 Pos(Item.Position.X, Item.Position.Y);
		int32 SlotIndex = Item.Position.W;
		
		bool bCanAdd = CheckItemCanAddFast(Item.ConfigId, Item.Num, Container, SlotIndex, Pos);
		if (!bCanAdd)
		{
			// 发送到邮箱或仓库
		}
		else
		{
			// Todo 进组
			InternalAddItem();
			Layout->DoOverlap(SlotIndex, Pos, Size, Item.Uid);
			auto* NewItem = ItemArray.Add();
			*NewItem = Item;
		}
	}
}

void UDInventoryComponent::SaveData(FDRoleInventoryData* OutData)
{
}

bool UDInventoryComponent::CheckItemCanAddFast(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector2 Pos) const
{
	if (const auto* CurrentItem = GetItemWithPos(Container, Slot, Pos))
	{
		const int32 MaxStack = 100;// Todo 从配置中获知最大堆叠
		if (CurrentItem->Num() + Num > MaxStack)
			return false;
	}
	else
	{
		const FDContainerLayout* Layout = SwitchContainer(Container);
		if (!Layout)
			return false;// 未指定容器
		
		// 当前位置没有道具
		const FIntVector2 Size = FIntVector2(1);// Todo 通过配置获取物品大小
		if (Layout->OverlapTestFast(Slot, Pos, Size))
			return false;
	}
	
	return true;
}

bool UDInventoryComponent::CheckItemCanAdd(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector2 Pos, TArray<FIntVector>& HitResult) const
{
	HitResult.Empty();
	if (const auto* CurrentItem = GetItemWithPos(Container, Slot, Pos))
	{
		const int32 MaxStack = 100;// Todo 从配置中获知最大堆叠
		if (CurrentItem->Num() + Num > MaxStack)
			return false;
	}
	else
	{
		const FDContainerLayout* Layout = SwitchContainer(Container);
		if (!Layout)
			return false;// 未指定容器
		
		// 当前位置没有道具
		const FIntVector2 Size = FIntVector2(1);// Todo 通过配置获取物品大小
		if (Layout->OverlapTest(Slot, Pos, Size, HitResult))
			return false;
	}
	
	return true;
}

const FDContainerLayout* UDInventoryComponent::SwitchContainer(const EDContainerType Container) const
{
	switch (Container)
	{
	case Pocket: return &Layout_Pocket;
	case Vest: return &Layout_Vest;
	case Backpack: return &Layout_BackPack;
	default: return nullptr;
	}
}

FDContainerLayout* UDInventoryComponent::SwitchContainer(const EDContainerType Container)
{
	switch (Container)
	{
	case Pocket: return &Layout_Pocket;
	case Vest: return &Layout_Vest;
	case Backpack: return &Layout_BackPack;
	default: return nullptr;
	}
}

const FDInventoryItem* UDInventoryComponent::GetItem(const int32 Id) const
{
	return ItemArray.GetItem(Id);
}

const FDInventoryItem* UDInventoryComponent::GetItemWithPos(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos) const
{
	const FDContainerLayout* Layout = SwitchContainer(Container);
	if (!Layout)
		return nullptr;// 未指定容器

	const int32 CurrentItemId = Layout->GetValue(Slot, Pos);
	const auto* CurrentItem = GetItem(CurrentItemId);
	if (!CurrentItem)
	{
		check(!CurrentItem)
		UE_LOG(LogProjectD, Error, TEXT("[InventoryModule]: 非法数据, 背包格子布局与实际背包内容不匹配, ItemId=%d"), CurrentItemId);
	}

	return CurrentItem;
}

void UDInventoryComponent::OnVestChange()
{
}

void UDInventoryComponent::OnBackPackChange()
{
}

void UDInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UDInventoryComponent, ItemArray, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
