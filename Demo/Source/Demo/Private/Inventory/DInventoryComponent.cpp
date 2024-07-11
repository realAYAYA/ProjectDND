#include "DInventoryComponent.h"

#include "Net/UnrealNetwork.h"


UDInventoryComponent::UDInventoryComponent()
{
	SetIsReplicated(true);
}

void UDInventoryComponent::LoadData(const FDRoleInventoryData& InData)
{
	// Todo 如果有一天容器或道具属性配置被修改，如何检测，变为非法的道具或容器应作何处理
	
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
			Layout->Spaces[i].Reset(Layout->Layouts[i].X, Layout->Layouts[i].Y);
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
		
		bool bCanAdd = Layout ? false : Layout->OverlapTestFast(SlotIndex, Pos, Size);
		if (!bCanAdd)
		{
			// 发送到邮箱或仓库
		}
		else
		{
			// 进组
			Layout->DoOverlap(SlotIndex, Pos, Size, Item.Uid);
			auto* NewItem = ItemArray.Add();
			*NewItem = Item;
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
