#include "DInventoryComponent.h"

#include "Character/DCharacter.h"
#include "Net/UnrealNetwork.h"


UDInventoryComponent::UDInventoryComponent()
{
	SetIsReplicatedByDefault(true);
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
		bool bCanAdd = CheckItemCanAddFast(Item.ConfigId, Item.Num, Container, Item.GetSlot(), FIntVector(Item.GetPos().X, Item.GetPos().Y, 0));
		if (!bCanAdd)
		{
			// 发送到邮箱或仓库
			// Todo 给玩家发送屏幕消息
			UE_LOG(LogProjectD, Warning, TEXT("[InventoryModule]: 道具CfgId %d 无法正常进包, 背包格子布局与实际背包内容不匹配, 可能是更新之后配置发生变化. 已移送至仓库"), Item.ConfigId);
		}
		else
		{
			InternalAddItem(Container, Item.GetSlot(), Item.GetPos(), Item.ConfigId, Item.Num);
		}
	}
}

void UDInventoryComponent::SaveData(FDRoleInventoryData* OutData)
{
}

bool UDInventoryComponent::CheckItemCanAddFast(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector Pos) const
{
	if (const auto* CurrentItem = GetItemWithPos(Container, Slot, FIntVector2(Pos.X, Pos.Y)))
	{
		const int32 MaxStack = 100;// Todo 从配置中获知最大堆叠
		if (CurrentItem->Num + Num > MaxStack)
			return false;
	}
	else
	{
		const FDContainerLayout* Layout = SwitchContainer(Container);
		if (!Layout)
			return false;// 未指定容器
		
		// 当前位置没有道具
		const FIntVector2 Size = FIntVector2(1);// Todo 通过配置获取物品大小
		if (Layout->OverlapTestFast(Slot, FIntVector2(Pos.X, Pos.Y), Size))
			return false;
	}
	
	return true;
}

bool UDInventoryComponent::CheckItemCanAdd(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector Pos, TArray<FIntVector>& HitResult) const
{
	HitResult.Empty();
	if (const auto* CurrentItem = GetItemWithPos(Container, Slot, FIntVector2(Pos.X, Pos.Y)))
	{
		const int32 MaxStack = 100;// Todo 从配置中获知最大堆叠
		if (CurrentItem->Num + Num > MaxStack)
			return false;
	}
	else
	{
		const FDContainerLayout* Layout = SwitchContainer(Container);
		if (!Layout)
			return false;// 未指定容器
		
		// 当前位置没有道具
		const FIntVector2 Size = FIntVector2(1);// Todo 通过配置获取物品大小
		if (!Layout->OverlapTest(Slot, FIntVector2(Pos.X, Pos.Y), Size, HitResult))
			return false;
	}
	
	return true;
}

int32 UDInventoryComponent::GetItemIdWithPos(const EDContainerType Container, const int32 Slot, const FIntVector Pos) const
{
	const FDContainerLayout* Layout = SwitchContainer(Container);
	if (!Layout)
		return 0;// 未指定容器

	const int32 CurrentItemId = Layout->GetValue(Slot, FIntVector2(Pos.X, Pos.Y));

	return CurrentItemId > 0 ? CurrentItemId : 0;
}

void UDInventoryComponent::DebugSetBackpack(const int32 X, const int32 Y)
{
	FDContainerLayout* Layout = SwitchContainer(EDContainerType::Backpack);
	if (!Layout->Layouts.IsValidIndex(0))
		Layout->Layouts.AddZeroed();
	
	Layout->Layouts[0].X = X;
	Layout->Layouts[0].Y = Y;

	while (!Layout->Spaces.IsValidIndex(0))
	{
		Layout->Spaces.AddZeroed();
	}
	
	Layout->Spaces[0].Reset(Layout->Layouts[0].X, Layout->Layouts[0].Y);
}

bool UDInventoryComponent::DebugCheckItemCanAdd(const FIntVector Pos, const FIntVector Size, TArray<FIntVector>& HitResult)
{
	const FDContainerLayout* Layout = SwitchContainer(EDContainerType::Backpack);
	if (!Layout)
		return false;// 未指定容器
		
	// 当前位置没有道具
	if (!Layout->OverlapTest(0, FIntVector2(Pos.X, Pos.Y), FIntVector2(Size.X, Size.Y), HitResult))
	{
		UE_LOG(LogProjectD, Warning, TEXT("[InventoryModule]: 空间不足"));
		return false;
	}

	return true;
}

void UDInventoryComponent::DebugAddItem(const int32 ItemUid, const FIntVector Pos, const FIntVector Size)
{
	FDContainerLayout* Layout = SwitchContainer(EDContainerType::Backpack);
	if (!Layout)
		return;// 未指定容器

	TArray<FIntVector> HitResult;
	if (!DebugCheckItemCanAdd(Pos, Size, HitResult))
		return;
	
	Layout->DoOverlap(0, FIntVector2(Pos.X, Pos.Y), FIntVector2(Size.X, Size.Y), ItemUid);// 空间填充
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

FDInventoryItem* UDInventoryComponent::GetItem(const int32 Id)
{
	return ItemArray.GetItem(Id);
}

const FDInventoryItem* UDInventoryComponent::GetItemWithPos(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos) const
{
	const FDContainerLayout* Layout = SwitchContainer(Container);
    	if (!Layout)
    		return nullptr;// 未指定容器
    
    	const int32 CurrentItemId = Layout->GetValue(Slot, Pos);
    	auto* CurrentItem = GetItem(CurrentItemId);
    	if (!CurrentItem)
    	{
    		check(!CurrentItem)
    		UE_LOG(LogProjectD, Error, TEXT("[InventoryModule]: 非法数据, 背包格子布局与实际背包内容不匹配, ItemId=%d"), CurrentItemId);
    	}
    
    	return CurrentItem;
}

FDInventoryItem* UDInventoryComponent::GetItemWithPos(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos)
{
	const FDContainerLayout* Layout = SwitchContainer(Container);
	if (!Layout)
		return nullptr;// 未指定容器

	const int32 CurrentItemId = Layout->GetValue(Slot, Pos);
	auto* CurrentItem = GetItem(CurrentItemId);
	if (!CurrentItem)
	{
		check(!CurrentItem)
		UE_LOG(LogProjectD, Error, TEXT("[InventoryModule]: 非法数据, 背包格子布局与实际背包内容不匹配, ItemId=%d"), CurrentItemId);
	}

	return CurrentItem;
}

void UDInventoryComponent::RemoveItemWithCfgId(const int32 CfgId, const int32 Num)
{
}

void UDInventoryComponent::OnVestChange()
{
}

void UDInventoryComponent::OnBackPackChange()
{
}

ADCharacter* UDInventoryComponent::GetCharacter() const
{
	return Cast<ADCharacter>(GetOwner());
}

FDInventoryItem* UDInventoryComponent::InternalAddItem(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos, const int32 CfgId, const int32 Num)
{
	// 检测配置
	{
		UE_LOG(LogProjectD, Error, TEXT("[InventoryModule]: 无效的道具配置, CfgId=%d"), CfgId);
	}

	const FIntVector2 Size(0);// 通过配置读取物品大小

	auto* CurrentItem = GetItemWithPos(Container, Slot, Pos);
	if (CurrentItem)
	{
		UE_LOG(LogProjectD, Log, TEXT("[InventoryModule]: 道具堆叠, ItemId=%d CfgId=%d"), CurrentItem->Uid, CfgId);
		CurrentItem->AddNum(Num);
	}
	else 
	{
		if (auto* Layout = SwitchContainer(Container))
		{
			CurrentItem = ItemArray.Add();
			CurrentItem->ConfigId = CfgId;
			CurrentItem->SetContainer(Container);
			CurrentItem->SetSlot(Slot);
			CurrentItem->SetPos(Pos);
			
			Layout->DoOverlap(Slot, Pos, Size, CurrentItem->Uid);// 空间填充
		
			UE_LOG(LogProjectD, Log, TEXT("[InventoryModule]: 新增道具, ItemId=%d CfgId=%d"), CurrentItem->Uid, CfgId);
		}
	}

	if (!CurrentItem)
	{
		UE_LOG(LogProjectD, Error, TEXT("[InventoryModule]: 创建道具失败, CfgId=%d"), CfgId);
	}

	return CurrentItem;
}

void UDInventoryComponent::InternalRemoveItem(const int32 Id)
{
	if (const auto Item = GetItem(Id))
	{
		// 先清理布局
		if (const auto Layout = SwitchContainer(Item->GetContainer()))
			Layout->ClearWithValue(Item->GetSlot(), Id);
		
		ItemArray.Remove(Item);// 再移除元素
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
