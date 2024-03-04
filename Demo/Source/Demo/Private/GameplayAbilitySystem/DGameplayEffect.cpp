#include "DGameplayEffect.h"
#include  "GameplayAbilitySystemGlobalTags.h"

FGameplayAbilityGlobalTags FGameplayAbilityGlobalTags::GasTags;

FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::GetActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle)
{
	for (FTurnBasedActiveGameplayEffect& Effect : GameplayEffects_Internal)
	{
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			return &Effect;
		}
	}
	
	return nullptr;
}

const FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::GetActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle) const
{
	for (const FTurnBasedActiveGameplayEffect& Effect : GameplayEffects_Internal)
	{
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			return &Effect;
		}
	}
	
	return nullptr;
}


FTurnBasedActiveGameplayEffect* FTurnBasedActiveGameplayEffectsContainer::ApplyActiveGameplayEffect(
	const FActiveGameplayEffectHandle& Handle)
{
	return nullptr;
}

bool FTurnBasedActiveGameplayEffectsContainer::RemoveActiveGameplayEffect(const FActiveGameplayEffectHandle& Handle)
{
	int32 Idx = INDEX_NONE;
	for (int32 i = 0; i < GameplayEffects_Internal.Num(); i++)
	{
		const FTurnBasedActiveGameplayEffect& Effect = GameplayEffects_Internal[i];
		if (Effect.ActiveGameplayEffectHandle == Handle)
		{
			Idx = i;
			break;
		}
	}

	if (Idx == INDEX_NONE)
		return false;
	
	GameplayEffects_Internal.RemoveAtSwap(Idx, 1, false);
	return true;
}

UDGameplayEffect::UDGameplayEffect()
{
	
}
