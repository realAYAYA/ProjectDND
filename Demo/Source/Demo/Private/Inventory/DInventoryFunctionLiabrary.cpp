#include "DInventoryFunctionLiabrary.h"

float UInventoryFunctionLibrary::CalculateItemWeight(const FDInventoryItem& Item)
{
	float TotalWeight = 0;

	if (Item.Container)
	{
		for (const auto& Id : Item.ItemData.Container)
		{
			if (const auto ItemN = Item.Container->GetItem(Id))
				TotalWeight += CalculateItemWeight(*ItemN);
		}
	}
	
	TotalWeight += 1;// Todo 计算自身重量
	
	return TotalWeight;
}
