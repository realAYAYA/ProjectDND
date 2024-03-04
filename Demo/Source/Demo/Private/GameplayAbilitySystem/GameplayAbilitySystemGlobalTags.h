#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

// 适合添加预设的Gas相关Tags
struct DEMO_API FGameplayAbilityGlobalTags final : public FGameplayTagNativeAdder
{
	FGameplayTag Paralysis;
	FGameplayTag Stun;
	FGameplayTag Sleep;
	FGameplayTag Fear;

	FGameplayTag Root;
	
	FGameplayTag Silence;

	FGameplayTag BattleState;
	
	FGameplayTag Test;
	
	virtual void AddTags() override
	{
		Paralysis	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis"), TEXT("ProjectT"));
		Stun		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Stun"), TEXT("ProjectT"));
		Sleep		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Sleep"), TEXT("ProjectT"));
		Fear		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Fear"), TEXT("ProjectT"));

		Root		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Root"), TEXT("ProjectT"));

		Silence		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Silence"), TEXT("ProjectT"));

		BattleState	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.Battle"), TEXT("ProjectT"));

		Test		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Test"), TEXT("ProjectT"));
	}

	FORCEINLINE static const FGameplayAbilityGlobalTags& Get() { return GasTags; }

private:

	static FGameplayAbilityGlobalTags GasTags;
};
