#pragma once
#include "GameCounter.h"
#include "QuestBase.Generated.h"

UENUM()
enum class EQuestState : uint8
{
	InValid,
	Accepted,
	Committable,
	Available,
	Finished,
	Failed
};

// 任务要求
USTRUCT(BlueprintType)
struct GAMESHARED_API FQuestRequirementItem
{

	GENERATED_USTRUCT_BODY()

	// 任务类型
	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 Type = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 TargetId = 0;

	UPROPERTY(EditDefaultsOnly, Category = "GameShared")
	int32 Num = 0;// 对应货物配置Id
};

// 货物道具
USTRUCT(BlueprintType)
struct GAMESHARED_API FQuestItem
{

	GENERATED_USTRUCT_BODY()

	// 任务Id, 或者叫配置Id
	UPROPERTY()
	int32 Id = 0;
	
	// 任务类型
	UPROPERTY()
	int32 Type = 0;
	
	UPROPERTY()
	TArray<FQuestRequirementItem> Requirements;

	UPROPERTY()
	FCounterLayer2 Counter;

	UPROPERTY()
	int64 BeginDate = 0;
	
	UPROPERTY()
	int32 TimeLimit = 0;
};

UCLASS()
class GAMESHARED_API UQuestSystemBase : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	EQuestState CheckState(const int32 Id);
	static EQuestState CheckState(const FQuestItem& Quest);

	UFUNCTION()
	void Update(const int32 Type, const int32 TargetId, const int32 Num = 1, const bool bOverride = false);
	static void UpdateSingleQuest(FQuestItem& Quest, const int32 Type, const int32 TargetId, const int32 Num = 1, const bool bOverride = false);
	
	UFUNCTION()
	virtual bool AcceptQuest(const int32 Id);

	UFUNCTION()
	virtual bool GiveUpQuest(const int32 Id);

	UFUNCTION()
	virtual bool SubmitQuest(const int32 Id);

	FQuestItem* GetQuest(const int32 Id);

protected:

	int32 GetQuestIndex(const int32 Id);
	
	FQuestItem& InternalAddQuest(const int32 Id);

	FQuestItem InternalRemoveQuest(const int32 Id);
	void InternalRemoveQuest(const FQuestItem* Quest);

	TArray<FQuestItem> QuestList;

	TSet<int32> AcceptedQuestIdList;

	TSet<int32> AvailableQuestIdList;
	
	TSet<int32> UnAcceptableQuestIdList;

	TSet<int32> FinishedQuestIdList;
};