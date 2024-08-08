#pragma once
#include "CoreMinimal.h"
#include "DInventoryComponent.h"
#include "DItemActor.generated.h"


// 容器组件：口袋，背包，背心
UCLASS()
class ADItemActor : public AActor
{
	GENERATED_BODY()

public:

	ADItemActor();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Use();

	// 使用(蓝图覆写), 该逻辑仅执行在服务器
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnUse"), Category = "ProjectD")
	bool BP_OnUse();

	// 拾取(蓝图覆写), 该逻辑仅执行在服务器
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPickUp"), Category = "ProjectD")
	bool BP_OnPickUp();

	// 能否使用(蓝图覆写)
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "CanUse"), Category = "ProjectD")
	bool BP_CanUse();

	// 能否拾取(蓝图覆写)
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "CanPickUp"), Category = "ProjectD")
	bool BP_CanPickUp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "ProjectD")
	int32 ItemId = 0;

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bUsing = false;
};


// 有着容器功能的Actor：背包、服装
UCLASS()
class ADContainerActor : public ADItemActor
{
	GENERATED_BODY()
	
public:
	
	ADContainerActor();

	virtual void PostNetInit() override;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Cancel();

	// 开启成功时触发, 该逻辑仅执行在服务器
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnOpen"), Category = "ProjectD")
	bool BP_OnOpen();

	// 能否打开(蓝图覆写)
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "CanOpen"), Category = "ProjectD")
	bool BP_CanOpen();

	void LoadData();
	void SaveData();
	
	void AddItem();

	void RemoveItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "ProjectD")
	bool bLock = false;

	// 容器布局Id
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing = OnLayoutChange, Category = "ProjectD")
	int32 ContainerLayoutId = 0;

protected:

	UFUNCTION()
	void OnLayoutChange();
	
	// 空间布局
	UPROPERTY()
	FDContainerLayout Layout;

	// 容器内道具
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;
};