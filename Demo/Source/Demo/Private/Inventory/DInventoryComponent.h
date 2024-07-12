#pragma once
#include "CoreMinimal.h"
#include "DGameTypes.h"
#include "DGameUtils.h"
#include "DInventoryComponent.generated.h"

class UDInventoryComponent;

USTRUCT(BlueprintType)
struct FDContainerLayout
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> Layouts;

	UPROPERTY(BlueprintReadOnly)
	TArray<FIntArray2D> Spaces;

	// 检测是否可以将一个给定Size的地块完成塞入，并返回塞入过程中的具体情况
	bool OverlapTest(const int32 SlotIndex, const FIntVector2 BeginPos, const FIntVector2 Size, TArray<FIntVector>& HitResult) const
	{
		HitResult.Reset();
		if (Spaces.IsValidIndex(SlotIndex))
			return Spaces[SlotIndex].OverlapTest(BeginPos, Size, HitResult);

		return false;
	}

	// 快速检测是否可以将一个给定Size的地块完成塞入
	bool OverlapTestFast(const int32 SlotIndex, const FIntVector2 BeginPos, const FIntVector2 Size) const
	{
		if (Spaces.IsValidIndex(SlotIndex))
			return Spaces[SlotIndex].OverlapTestFast(BeginPos, Size);

		return false;
	}

	void DoOverlap(const int32 SlotIndex, const FIntVector2 BeginPos, const FIntVector2 Size, const int32 Value)
	{
		if (Spaces.IsValidIndex(SlotIndex))
			Spaces[SlotIndex].DoOverlap(BeginPos, Size, Value);
	}
};

// 容器组件：口袋，背包，背心
UCLASS()
class UDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDInventoryComponent();
	
	void LoadData(const FDRoleInventoryData& InData);
	void SaveData(FDRoleInventoryData* OutData);

	// 移动道具，同一容器中移动，不同容器之间移动
	bool MoveItem(const int32 ItemId, const FIntVector3 NewPosition);
	
	// 穿装备 脱装备
	bool PutOn(const int32 ItemId, const int32 Slot);
	bool TakeOff(const int32 ItemId);
	
	FDInventoryItem* GetItem(const int32 Id);

	int64 GetItemNumWithCfgId(const int32 CfgId) const;

	// 删除道具，根据数量不一定是移除道具
	void DeleteItem(const int32 Id, const int32 Num, const FString& Reason);
	void DeleteItemWithCfgId(const int32 CfgId, const int32 Num, const FString& Reason);

	bool AutoAddItem(FDInventoryItem* Item, const FString& Reason);
	bool AddItem(FDInventoryItem* Item, const FString& Reason);
	bool AddItemWithCfgId(const int32 CfgId, const int32 Num, const FString& Reason);
	

	void RemoveItem(const int32 Id);
	
protected:

	void InternalAddItem();
	
	// 道具数组
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;

	// 容器配置Id，配置中可以含有更多表现相关的参数（比如决定UI的样式）
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, ReplicatedUsing = OnContainerChange);
	int32 VestId = 0;

	// 口袋容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated);
	int32 PocketId = 0;
	
	// 背包容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, ReplicatedUsing = OnContainerChange);
	int32 BackPackId = 0;

	// 容器布局
	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_Vest;

	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_Pocket;// 比如塔科夫的口袋就是4个'1x1'
	
	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_BackPack;

	UFUNCTION()
	void OnContainerChange();
};
