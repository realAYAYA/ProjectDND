#include "DTargetActor.h"

#include "GameplayAbilitySystem/Abilities/DGameplayAbility.h"

ADTargetActor::ADTargetActor(const FObjectInitializer& ObjectInitializer)
{
	ShouldProduceTargetDataOnServer = false;// 要求玩家发送目标数据
	bDebug = false;
	bDestroyOnConfirmation = true;

	//bReplicates = true;
}

bool ADTargetActor::SetAbilityInfo(APlayerController* PC, UAbilitySystemComponent* Asc, const FGameplayTag& Tag)
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

	if (!AbilityInstance->IsPredictingClient() && ShouldProduceTargetDataOnServer)
		return false;
	
	PrimaryPC = PC;
	StartTargeting(AbilityInstance);
	BindToConfirmCancelInputs();
	
	TargetDataReadyDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data)
	{
		const FGameplayTag ApplicationTag; // Fixme: where would this be useful?
		Asc->CallServerSetReplicatedTargetData(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Data, ApplicationTag, Asc->ScopedPredictionKey);
	});

	CanceledDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data)
	{
		Asc->ServerSetReplicatedTargetDataCancelled(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Asc->ScopedPredictionKey );
	});
	
	return true;
}

bool ADTargetActor::SetAbilityInfoByClass(APlayerController* PC, UAbilitySystemComponent* Asc, const TSubclassOf<UDGameplayAbility>& AbilityClass)
{
	const auto* GameplayAbility = AbilityClass->GetDefaultObject<UDGameplayAbility>();
	return SetAbilityInfo(PC, Asc, GameplayAbility->AbilityTags.First());
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
