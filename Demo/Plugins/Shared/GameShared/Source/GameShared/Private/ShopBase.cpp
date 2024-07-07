#include "ShopBase.h"

UShopBase::UShopBase(const FObjectInitializer& ObjectInitializer)
{
}

FShopGoodsItem* UShopBase::FindGoodsItem(const int32 GoodsIndex)
{
	for (auto& Item : Goods)
	{
		if (Item.Index == GoodsIndex)
			return &Item;
	}

	return nullptr;
}

bool UShopBase::CheckStock(const FShopGoodsItem* Item, const int32 Num)
{
	if (Item)
	{
		if (Item->Stock < 0)
			return true;// 无限购买
		
		if (Item->Stock > 0 && Item->Stock >= Num)
			return true;
	}

	return false;
}

void UShopBase::InternalBuy(FShopGoodsItem* Item, const int32 Num)
{
	if (Item && Num > 0)
	{
		if (Item->Stock >= Num)
			Item->Stock -= Num;
	}
}

FShopGoodsItem& UShopBase::InternalAdd()
{
	FShopGoodsItem& Item = Goods[Goods.AddZeroed()];
	
	// 为其分配唯一商品Index
	{
		int32 i  = 0;
		while (!FindGoodsItem(i))
			++i;
		
		Item.Index = i;
	}
	
	return Item;
}

FShopGoodsItem UShopBase::InternalRemove(const int32 Index)
{
	FShopGoodsItem Out;
	int32 i = 0;
	for (; i < Goods.Num(); i++)
	{
		if (Goods[i].Index == Index)
		{
			Out = Goods[i];
			break;
		}
	}

	if (i < Goods.Num())
		Goods.RemoveAtSwap(i, 1, false);

	return Out;
}

void UShopBase::InternalRemove(const FShopGoodsItem* Item)
{
	if (Item)
	{
		int32 i = 0;
		for (; i < Goods.Num(); i++)
		{
			if (Goods[i].Index == Item->Index) break;
		}

		if (i < Goods.Num())
			Goods.RemoveAtSwap(i, 1, false);
	}
}

void UShopBase::Reset()
{
	Goods.Reset();
}
