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

	UPROPERTY(Replicated)
	int32 ItemId = 0;
};


// 有着容器功能的Actor：背包、服装
UCLASS()
class ADContainerActor : public ADItemActor
{
	GENERATED_BODY()

protected:

	ADContainerActor();

	// 容器布局Id
	UPROPERTY(Replicated)
	int32 ContainerLayoutId = 0;

	// 空间布局
	UPROPERTY()
	FDContainerLayout Layout;

	// 容器内道具
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;

	/*
	void AddItem(const int32 Id, const int32 Num);
	void DeleteItem(const int32 Id, const int32 Num);
	void RemoveItem();
	*/

	virtual void PostNetInit() override;
};