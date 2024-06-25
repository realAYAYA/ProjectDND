// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemBlueprintLibrary.h"

#include "AbilitySystemComponent.h"

int32 UDAbilitySystemBlueprintLibrary::GetActiveGameplayEffectTotalTurn(FActiveGameplayEffectHandle ActiveHandle)
{
	UAbilitySystemComponent* ASC = ActiveHandle.GetOwningAbilitySystemComponent();
	if (ASC)
	{
		if (const FActiveGameplayEffect* ActiveGE = ASC->GetActiveGameplayEffect(ActiveHandle))
		{
			return ActiveGE->GetDuration();
		}
	}
	
	return 0;
}

int32 UDAbilitySystemBlueprintLibrary::GetActiveGameplayEffectRemainingTurn(FActiveGameplayEffectHandle ActiveHandle)
{
	UAbilitySystemComponent* ASC = ActiveHandle.GetOwningAbilitySystemComponent();
	if (ASC)
	{
		if (const FActiveGameplayEffect* ActiveGE = ASC->GetActiveGameplayEffect(ActiveHandle))
		{
			return ActiveGE->GetDuration();
		}
	}
	
	return 0;
}

bool UDAbilitySystemBlueprintLibrary::EffectContextHasCritHit(FGameplayEffectContextHandle EffectContext, float& CirtValue)
{
	CirtValue = 0;
	if (const auto* CritParams = EffectContext.GetHitResult())
	{
		CirtValue = CritParams->Distance;
	}

	return false;
}
