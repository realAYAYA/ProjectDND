#include "DItemActor.h"

#include "Net/UnrealNetwork.h"

void ADItemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADItemActor, ItemId, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADItemActor, bUsing, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


ADItemActor::ADItemActor()
{
	bUsing = false;
}

void ADItemActor::Use()
{
}

bool ADItemActor::BP_OnUse_Implementation()
{
	return true;
}

bool ADItemActor::BP_OnPickUp_Implementation()
{
	return true;
}

bool ADItemActor::BP_CanUse_Implementation()
{
	return true;
}

bool ADItemActor::BP_CanPickUp_Implementation()
{
	return true;
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

bool ADContainerActor::BP_OnOpen_Implementation()
{
	return true;
}

bool ADContainerActor::BP_CanOpen_Implementation()
{
	return true;
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
	DOREPLIFETIME_WITH_PARAMS_FAST(ADContainerActor, bLock, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADContainerActor, ContainerLayoutId, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADContainerActor, ItemArray, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
