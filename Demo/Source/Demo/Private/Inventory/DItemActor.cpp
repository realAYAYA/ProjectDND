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


ADContainerActor::ADContainerActor()
{
}

void ADContainerActor::PostNetInit()
{
	Super::PostNetInit();
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
