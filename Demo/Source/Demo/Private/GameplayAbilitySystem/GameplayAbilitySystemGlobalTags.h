#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

// 适合添加预设的Gas相关Tags
struct DEMO_API FGameplayAbilityGlobalTags final : public FGameplayTagNativeAdder
{
	FGameplayTag Test;
	
	FGameplayTag Paralysis;
	FGameplayTag Stun;
	FGameplayTag Sleep;
	FGameplayTag Fear;

	FGameplayTag Root;
	
	FGameplayTag Silence;

	FGameplayTag InBattle;

	FGameplayTag Buff;
	FGameplayTag DeBuff;
	
	FGameplayTag Move;
	
	virtual void AddTags() override
	{
		if (GasTags.Test.IsValid())
			return;
		
		Paralysis	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis"), TEXT("ProjectD"));
		Stun		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Stun"), TEXT("ProjectD"));
		Sleep		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Sleep"), TEXT("ProjectD"));
		Fear		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Fear"), TEXT("ProjectD"));

		Root		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Root"), TEXT("ProjectD"));

		Silence		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Silence"), TEXT("ProjectD"));

		InBattle	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Battle"), TEXT("ProjectD"));

		Buff		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.Buff"), TEXT("ProjectD"));
		DeBuff		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.DeBuff"), TEXT("ProjectD"));

		Move		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Movement.Move"), TEXT("ProjectD"));

		Test		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Test"), TEXT("ProjectD"));
	}

	static bool IsDeBuff(const FGameplayTag& Tag) { return false; }

	FORCEINLINE static const FGameplayAbilityGlobalTags& Get()
	{
		return GasTags;
	}

	// 一种在编译阶段Get方法
	FORCEINLINE static FGameplayAbilityGlobalTags& GetPreConstruct()
	{
		if (!GasTags.Test.IsValid())
			GasTags.AddTags();
		
		return GasTags;
	}

private:

	static FGameplayAbilityGlobalTags GasTags;
};
