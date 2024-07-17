﻿#pragma once
#include "CoreMinimal.h"
#include "DGameTypes.h"
#include "DGameUtils.h"
#include "DInventoryComponent.generated.h"

class ADCharacter;
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
	bool OverlapTest(const int32 Slot, const FIntVector2 BeginPos, const FIntVector2 Size, TArray<FIntVector>& HitResult) const
	{
		HitResult.Reset();
		if (Spaces.IsValidIndex(Slot))
			return Spaces[Slot].OverlapTest(BeginPos, Size, HitResult);

		return false;
	}

	// 快速检测是否可以将一个给定Size的地块完成塞入
	bool OverlapTestFast(const int32 Slot, const FIntVector2 BeginPos, const FIntVector2 Size) const
	{
		if (Spaces.IsValidIndex(Slot))
			return Spaces[Slot].OverlapTestFast(BeginPos, Size);

		return false;
	}

	void DoOverlap(const int32 Slot, const FIntVector2 BeginPos, const FIntVector2 Size, const int32 Value)
	{
		if (Spaces.IsValidIndex(Slot))
			Spaces[Slot].DoOverlap(BeginPos, Size, Value);
	}

	int32 GetValue(const int32 Slot, const FIntVector2 Pos) const
	{
		if (Spaces.IsValidIndex(Slot))
			return Spaces[Slot].Get(Pos.X, Pos.Y);

		return -1;
	}
	
	void ClearWithValue(const int32 Slot, const int32 Value)
	{
		if (Spaces.IsValidIndex(Slot))
			Spaces[Slot].SetWithValue(Value, 0);
	}
};

// 容器组件：口袋，背包，背心
UCLASS(BlueprintType)
class UDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UDInventoryComponent();
	
	void LoadData(const FDRoleInventoryData& InData);
	void SaveData(FDRoleInventoryData* OutData);

	//UFUNCTION(BlueprintCallable, Category = "ProjectD")
	//bool k2_CheckItemCanAddFast(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FVector2D Pos) const;

	
	bool CheckItemCanAddFast(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector2 Pos) const;

	//UFUNCTION(BlueprintCallable, Category = "ProjectD")
	//bool K2_CheckItemCanAdd(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FVector2D Pos, TArray<FIntVector>& HitResult) const;

	
	bool CheckItemCanAdd(const int32 CfgId, const int32 Num, const EDContainerType Container, const int32 Slot, const FIntVector2 Pos, TArray<FIntVector>& HitResult) const;

protected:
	
	// 道具数组
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;

	// 容器配置Id，配置中可以含有更多表现相关的参数（比如决定UI的样式）
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, ReplicatedUsing = OnVestChange);
	int32 VestId = 0;

	// 口袋容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated);
	int32 PocketId = 0;
	
	// 背包容器Id
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, ReplicatedUsing = OnBackPackChange);
	int32 BackPackId = 0;

	// 容器布局
	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_Vest;

	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_Pocket;// 比如塔科夫的口袋就是4个'1x1'
	
	UPROPERTY(BlueprintReadOnly)
	FDContainerLayout Layout_BackPack;

	const FDContainerLayout* SwitchContainer(const EDContainerType Container) const;
	FDContainerLayout* SwitchContainer(const EDContainerType Container);

	const FDInventoryItem* GetItem(const int32 Id) const;
	FDInventoryItem* GetItem(const int32 Id);
	const FDInventoryItem* GetItemWithPos(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos) const;
	FDInventoryItem* GetItemWithPos(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos);

	void RemoveItemWithCfgId(const int32 CfgId, const int32 Num);
	
	UFUNCTION()
	void OnVestChange();

	UFUNCTION()
	void OnBackPackChange();

	ADCharacter* GetCharacter() const;
		
private:

	FDInventoryItem* InternalAddItem(const EDContainerType Container, const int32 Slot, const FIntVector2 Pos, const int32 CfgId, const int32 Num);

	void InternalRemoveItem(const int32 Id);
};

