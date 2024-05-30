#include "DTargetActor.h"
#include "GameplayAbilitySystem/Abilities/GA_WithTargetData.h"

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
	
	return InitTargetActor(PC, Asc, *Spec);
}

bool ADTargetActor::SetAbilityInfoByClass(APlayerController* PC, UAbilitySystemComponent* Asc, const TSubclassOf<UDGameplayAbility>& AbilityClass)
{
	if (!Asc || !PC)
		return false;
	
	const auto* Spec = Asc->FindAbilitySpecFromClass(AbilityClass);
	if (!Spec)
		return false;
	
	return InitTargetActor(PC, Asc, *Spec);
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

bool ADTargetActor::InitTargetActor(APlayerController* PC, UAbilitySystemComponent* Asc, const FGameplayAbilitySpec& Spec)
{
	if (Spec.GetAbilityInstances().Num() <= 0)
		return false;
	
	auto* AbilityInstance = Cast<UGA_WithTargetData>(Spec.GetPrimaryInstance());
	if (!AbilityInstance)
		return false;

	if (!AbilityInstance->IsPredictingClient() && ShouldProduceTargetDataOnServer)
		return false;
	
	PrimaryPC = PC;
	StartTargeting(AbilityInstance);
	BindToConfirmCancelInputs();

	// 如果不是主机需要发送数据到主机
	if (!Asc->GetOwner()->HasAuthority())
	{
		TargetDataReadyDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data){
			const FGameplayTag ApplicationTag; // Fixme: where would this be useful?
			Asc->CallServerSetReplicatedTargetData(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Data, ApplicationTag, Asc->ScopedPredictionKey);
		});

		CanceledDelegate.AddLambda([Asc, AbilityInstance](const FGameplayAbilityTargetDataHandle& Data){
			Asc->ServerSetReplicatedTargetDataCancelled(AbilityInstance->GetCurrentAbilitySpecHandle(), AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey(), Asc->ScopedPredictionKey );
		});
	}
	
	// Todo 但不管是不是主机，即使是客户端也需要对自己本地技能发送数据, 理由是技能施放者（客户端）不能自己表现攻击结束动作
	// If we spawned the target actor, always register the callbacks for when the data is ready.
	TargetDataReadyDelegate.AddUObject(AbilityInstance, &UGA_WithTargetData::ReceiveTargetData);
	CanceledDelegate.AddUObject(AbilityInstance, &UGA_WithTargetData::ReceiveTargetData);
	
	return true;
}
