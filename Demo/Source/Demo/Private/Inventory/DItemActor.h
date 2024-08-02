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

	// 使用场景中容器触发事件
	UFUNCTION(BlueprintNativeEvent)
	void BP_Use();

	UPROPERTY(Replicated)
	int32 ItemId = 0;

	UPROPERTY(Replicated)
	bool bUsing;
};


// 有着容器功能的Actor：背包、服装
UCLASS()
class ADContainerActor : public ADItemActor
{
	GENERATED_BODY()
	
public:
	
	ADContainerActor();

	// 容器布局Id
	UPROPERTY(ReplicatedUsing = OnLayoutChange)
	int32 ContainerLayoutId = 0;

	virtual void PostNetInit() override;

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Cancel();

	// 开启场景中容器触发事件
	UFUNCTION(BlueprintNativeEvent)
	void BP_Open();

	void LoadData();
	void SaveData();
	
	void AddItem();

	void RemoveItem();

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