#include "DGameplayEffect.h"
#include  "GameplayAbilitySystemGlobalTags.h"

FGameplayAbilityGlobalTags FGameplayAbilityGlobalTags::GasTags;

void FTurnBasedActiveGameplayEffect::PreReplicatedRemove(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
}

void FTurnBasedActiveGameplayEffect::PostReplicatedAdd(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
}

void FTurnBasedActiveGameplayEffect::PostReplicatedChange(const FTurnBasedActiveGameplayEffectsContainer& InArray)
{
}

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
	const FActiveGameplayEffectHandle& Handle,
	const UDGameplayEffect* GameplayEffect)
{
	FTurnBasedActiveGameplayEffect* TurnBasedActiveGameplayEffect = GetActiveGameplayEffect(Handle);
	if (!TurnBasedActiveGameplayEffect)
	{
		const int32 Idx = GameplayEffects_Internal.Add(FTurnBasedActiveGameplayEffect(Handle, GameplayEffect->TurnDuration));
		return &GameplayEffects_Internal[Idx];
	}
	else
	{
		if (GameplayEffect->StackDurationRefreshPolicy == EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication)
		{
			TurnBasedActiveGameplayEffect->DurationTurn = GameplayEffect->TurnDuration;
		}

		if (GameplayEffect->StackPeriodResetPolicy == EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication)
		{
			TurnBasedActiveGameplayEffect->CurrentTurn = 0;
		}
	}

	return TurnBasedActiveGameplayEffect;
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
	
	GameplayEffects_Internal.RemoveAtSwap(Idx);
	return true;
}

void FTurnBasedActiveGameplayEffectsContainer::CheckTurnDuration()
{
	
}

UDGameplayEffect::UDGameplayEffect()
{
	
}
