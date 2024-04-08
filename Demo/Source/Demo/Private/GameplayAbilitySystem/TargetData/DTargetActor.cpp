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

	const FGameplayAbilitySpec* Spec = Asc->FindAbilitySpecFromHandle(OutAbilityHandles[0]);
	if (!Spec)
		return false;
	
	return InternalInitTargetActor(PC, Asc, *Spec);
}

bool ADTargetActor::SetAbilityInfoByClass(APlayerController* PC, UAbilitySystemComponent* Asc, const TSubclassOf<UDGameplayAbility>& AbilityClass)
{
	if (!Asc || !PC)
		return false;
	
	const auto* Spec = Asc->FindAbilitySpecFromClass(AbilityClass);
	if (!Spec)
		return false;
	
	return InternalInitTargetActor(PC, Asc, *Spec);
}

void ADTargetActor::K2_ConfirmTargeting(const FGameplayAbilityTargetDataHandle& InTargetDataHandle)
{
	TargetDataHandle = InTargetDataHandle;

	ConfirmTargeting();
}

void ADTargetActor::K2_CancelTargeting()
{
	OwningAbility->K2_CancelAbility();
	this->CancelTargeting();
}

void ADTargetActor::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

bool ADTargetActor::InternalInitTargetActor(APlayerController* PC, UAbilitySystemComponent* Asc, const FGameplayAbilitySpec& Spec)
{
	if (Spec.GetAbilityInstances().Num() <= 0)
		return false;
	
	auto* AbilityInstance = Cast<UGA_WithProjectile>(Spec.GetAbilityInstances()[0]);
	if (!AbilityInstance)
		return false;

	if (!AbilityInstance->IsPredictingClient() && ShouldProduceTargetDataOnServer)
		return false;
	
	PrimaryPC = PC;
	StartTargeting(AbilityInstance);
	BindToConfirmCancelInputs();

	// 如果是主机直接发送数据到Ability不用网络RPc
	if (Asc->GetOwner()->HasAuthority())
	{
		// If we spawned the target actor, always register the callbacks for when the data is ready.
		TargetDataReadyDelegate.AddUObject(AbilityInstance, &UGA_WithProjectile::ReceiveTargetData);
		CanceledDelegate.AddUObject(AbilityInstance, &UGA_WithProjectile::ReceiveTargetData);
	}
	else
	{
		TargetDataReadyDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data){
			const FGameplayTag ApplicationTag; // Fixme: where would this be useful?
			Asc->CallServerSetReplicatedTargetData(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Data, ApplicationTag, Asc->ScopedPredictionKey);
		});

		CanceledDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data){
			Asc->ServerSetReplicatedTargetDataCancelled(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Asc->ScopedPredictionKey );
		});
	}
	
	return true;
}
