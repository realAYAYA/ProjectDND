#include "DItemActor.h"

#include "Net/UnrealNetwork.h"

void ADItemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADItemActor, ItemId, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


ADItemActor::ADItemActor()
{
	bUsing = false;
}

void ADItemActor::Use()
{
}

void ADItemActor::BP_Use_Implementation()
{
	
}


ADContainerActor::ADContainerActor()
{
}

void ADContainerActor::PostNetInit()
{
	Super::PostNetInit();
}

void ADContainerActor::Open()
{
	bUsing = true;
}

void ADContainerActor::Cancel()
{
	bUsing = false;
}

void ADContainerActor::BP_Open_Implementation()
{
	
}

void ADContainerActor::LoadData()
{
}

void ADContainerActor::SaveData()
{
}

void ADContainerActor::AddItem()
{
}

void ADContainerActor::RemoveItem()
{
}

void ADContainerActor::OnLayoutChange()
{
	
}

void ADContainerActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADContainerActor, ContainerLayoutId, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADContainerActor, ItemArray, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
