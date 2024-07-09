#pragma once
#include "InventoryBase.generated.h"

USTRUCT(BlueprintType)
struct GAMESHARED_API FInventoryItemBase
{
	GENERATED_USTRUCT_BODY()

	//FTurnBasedActiveGameplayEffect& operator=(FTurnBasedActiveGameplayEffect&& Other) noexcept;

	//FTurnBasedActiveGameplayEffect& operator=(const FTurnBasedActiveGameplayEffect& Other);

	//void PreReplicatedRemove(const FInventoryItemsContainer &InArray);
	//void PostReplicatedAdd(const FInventoryItemsContainer &InArray);
	//void PostReplicatedChange(const FInventoryItemsContainer &InArray);

	UPROPERTY(BlueprintReadOnly)
	int64 Uid = 0;
	
	// 堆叠数量
	UPROPERTY(BlueprintReadOnly)
	int64 Num = 0;

	// 生成日期
	UPROPERTY(BlueprintReadOnly)
	int64 BeginDate = 0;

	// 道具配置Id
	UPROPERTY(BlueprintReadOnly)
	int32 ConfigId = 0;

	// 背包中的位置，zw变量可根据需求解析，例如位于背心中的某个插槽
	UPROPERTY(BlueprintReadOnly)
	FIntVector4 Position;
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