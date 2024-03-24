#include "GA_Fireball.h"

#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

void UGA_Fireball::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto* Asc = GetDAbilitySystemComponent(ActorInfo);
	if (Asc)
	{
		Asc->OnAbilityReadyToFire.AddDynamic(this, &UGA_Fireball::OnFire);
	}
}

void UGA_Fireball::OnFire(const UClass* AbilityClass)
{
	if (AbilityClass && AbilityClass != this->StaticClass())
		return;

	UAnimInstance* AnimInstance = CurrentActorInfo->GetAnimInstance();
	AnimInstance->NotifyQueue
}
