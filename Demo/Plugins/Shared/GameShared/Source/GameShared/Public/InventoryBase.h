#pragma once
#include "InventoryBase.generated.h"

USTRUCT()
struct GAMESHARED_API FInventoryItemBase
{
	GENERATED_USTRUCT_BODY()

	//FTurnBasedActiveGameplayEffect& operator=(FTurnBasedActiveGameplayEffect&& Other) noexcept;

	//FTurnBasedActiveGameplayEffect& operator=(const FTurnBasedActiveGameplayEffect& Other);

	//void PreReplicatedRemove(const FInventoryItemsContainer &InArray);
	//void PostReplicatedAdd(const FInventoryItemsContainer &InArray);
	//void PostReplicatedChange(const FInventoryItemsContainer &InArray);

	// 堆叠数量
	UPROPERTY()
	int32 Stack = 0;

	// 生成日期
	UPROPERTY()
	int64 BeginDate = 0;

	UPROPERTY()
	int32 ConfigId = 0;

	UPROPERTY()
	int32 Uid = 0;
};

class GAMESHARED_API FInventoryBase/* : public UObject*/
{
	/*GENERATED_BODY()*/
	
public:

protected:

	int32 GetItemNumWithCfgId(const int32 ConfigId);

	int32 GetItemNum(const int64 Id);

	bool AddItem(const int64 Id, const int32 Num, const FString& Reason);
	bool AddItemWithCfgId(const int64 Id, const int32 Num, const FString& Reason);
	
	void DeleteItem(const int64 Id, const int32 Num, const FString& Reason);
	void DeleteItemWithCfgId(const int64 Id, const int32 Num, const FString& Reason);
	
};