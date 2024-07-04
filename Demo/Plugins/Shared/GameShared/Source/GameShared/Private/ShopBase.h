#pragma once
#include "CoreMinimal.h"
#include "ShopBase.generated.h"

// 货物道具
USTRUCT(BlueprintType)
struct GAMESHARED_API FShopGoodsItem
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 Index = 0;

	struct FSingleItemData
	{
		int32 ItemId = 0;
		int32 Num = 0;
	};

	TArray<FSingleItemData> Items;// 货物中的道具清单，一个商品中可能不只包含一个道具

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 Stock = -1;// 库存，Stock < 0为无限购买

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 Price = 0;

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	float Discount = 1.0f;// 折扣

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 ConfigId = 0;// 对应货物配置Id

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	bool bRecommend = false;// 标记为推荐
};

UCLASS()
class GAMESHARED_API UShopBase : public UObject
{

	GENERATED_BODY()
	
public:

	UShopBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//bool Buy(const int32 GoodsIndex, const int32 Num = 1);
	//bool Sell();
	//void Refresh(const bool bForce = false);

	FShopGoodsItem* FindGoodsItem(const int32 GoodsIndex);

protected:

	bool CheckStock(const FShopGoodsItem* Item, const int32 Num);

	void InternalBuy(FShopGoodsItem* Item, const int32 Num = 1);

	FShopGoodsItem& InternalAdd();
	FShopGoodsItem InternalRemove(const int32 Index);
	void InternalRemove(const FShopGoodsItem* Item);

	void Reset();// 重置商店

	UPROPERTY()
	TArray<FShopGoodsItem> Goods;
};
