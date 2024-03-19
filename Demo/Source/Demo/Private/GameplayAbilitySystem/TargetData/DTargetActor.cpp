#include "DTargetActor.h"

ADTargetActor::ADTargetActor(const FObjectInitializer& ObjectInitializer)
{
	ShouldProduceTargetDataOnServer = false;// 要求玩家发送目标数据
	bDebug = false;
	bDestroyOnConfirmation = true;

	//bReplicates = true;
}

bool ADTargetActor::SetAbilityInfo(APlayerController* PC, const UAbilitySystemComponent* Asc, const FGameplayTag& Tag)
{
	if (!Asc || !PC)
		return false;
	
	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	FGameplayTagContainer Container;
	Container.AddTag(Tag);
	Asc->FindAllAbilitiesWithTags(OutAbilityHandles, Container);
	if (OutAbilityHandles.Num() == 0)
		return false;

	const FGameplayAbilitySpec* AbilitySpec = Asc->FindAbilitySpecFromHandle(OutAbilityHandles[0]);
	if (!AbilitySpec)
	{
		return false;
	}

	// try to get the ability instance
	UGameplayAbility* AbilityInstance = AbilitySpec->GetPrimaryInstance();
	if (!AbilityInstance)
	{
		return false;
	}
	
	PrimaryPC = PC;
	StartTargeting(AbilityInstance);
	BindToConfirmCancelInputs();
	
	return true;
}

void ADTargetActor::K2_ConfirmTargeting(const FGameplayAbilityTargetDataHandle& InTargetDataHandle)
{
	TargetDataHandle = InTargetDataHandle;

	ConfirmTargeting();
}

void ADTargetActor::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}
