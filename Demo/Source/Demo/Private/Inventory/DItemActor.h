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
	int32 ContainerLayout = 0;

	// 空间布局
	UPROPERTY()
	TArray<FVector2D> Spaces;

	// 容器内道具
	UPROPERTY(Replicated)
	FDInventoryItemsContainer ItemArray;

	virtual void PostNetInit() override;
};