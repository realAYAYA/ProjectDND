#include "DGameplayAbility.h"

#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

UDAbilitySystemComponent* UDGameplayAbility::GetDAbilitySystemComponent(const FGameplayAbilityActorInfo* ActorInfo)
{
	if (ActorInfo)
	{
		if (const auto* Character = Cast<ADCharacter>(ActorInfo->AvatarActor.Get()))
			return Character->AbilitySystemComponent;
	}

	return nullptr;
}
