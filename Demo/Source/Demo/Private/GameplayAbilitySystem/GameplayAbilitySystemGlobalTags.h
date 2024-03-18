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
	
	FGameplayTag Move;
	
	FGameplayTag Test;
	
	virtual void AddTags() override
	{
		Paralysis	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis"), TEXT("ProjectD"));
		Stun		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Stun"), TEXT("ProjectD"));
		Sleep		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Sleep"), TEXT("ProjectD"));
		Fear		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Fear"), TEXT("ProjectD"));

		Root		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Root"), TEXT("ProjectD"));

		Silence		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Silence"), TEXT("ProjectD"));

		BattleState	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.Battle"), TEXT("ProjectD"));

		Move		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Movement.Move"), TEXT("ProjectD"));

		//Test		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Test"), TEXT("ProjectD"));
	}

	static bool IsDeBuff(const FGameplayTag& Tag) { return false; }

	FORCEINLINE static const FGameplayAbilityGlobalTags& Get() { return GasTags; }

private:

	static FGameplayAbilityGlobalTags GasTags;
};
