#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

// 适合添加预设的Gas相关Tags
struct DEMO_API FGameplayAbilityGlobalTags final : public FGameplayTagNativeAdder
{
	FGameplayTag InBattle;
	FGameplayTag MyBattle;
	
	FGameplayTag AbilityHit;
	FGameplayTag HitByPhyMelee;
	FGameplayTag HitByPhyRange;
	FGameplayTag HitByMagMelee;
	FGameplayTag HitByMagRange;
	
	FGameplayTag Paralysis;
	FGameplayTag Stun;
	FGameplayTag Sleep;
	FGameplayTag Fear;

	FGameplayTag Root;
	
	FGameplayTag Silence;
	
	FGameplayTag Buff;
	FGameplayTag DeBuff;
	
	FGameplayTag Move;
	
	virtual void AddTags() override
	{
		if (GasTags.InBattle.IsValid())
			return;

		InBattle	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Rules.InBattle"), TEXT("ProjectD"));
		MyBattle	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Rules.MyTurn"), TEXT("ProjectD"));

		AbilityHit	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Passion.Hit"), TEXT("ProjectD"));
		HitByPhyMelee	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Passion.Hit.Melee.Phy"), TEXT("ProjectD"));
		HitByPhyRange	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Passion.Hit.Range.Phy"), TEXT("ProjectD"));
		HitByMagMelee	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Passion.Hit.Melee.Mag"), TEXT("ProjectD"));
		HitByMagRange	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Passion.Hit.Range.Mag"), TEXT("ProjectD"));
		
		Paralysis	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis"), TEXT("ProjectD"));
		Stun		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Stun"), TEXT("ProjectD"));
		Sleep		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Sleep"), TEXT("ProjectD"));
		Fear		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Fear"), TEXT("ProjectD"));

		Root		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Root"), TEXT("ProjectD"));

		Silence		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Silence"), TEXT("ProjectD"));

		Buff		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.Buff"), TEXT("ProjectD"));
		DeBuff		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.DeBuff"), TEXT("ProjectD"));

		Move		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Movement.Move"), TEXT("ProjectD"));
	}

	static bool IsDeBuff(const FGameplayTag& Tag) { return false; }
	static bool HitByMelee(const FGameplayTag& Tag) { return false; }
	static bool HitBySpell(const FGameplayTag& Tag) { return false; }

	FORCEINLINE static const FGameplayAbilityGlobalTags& Get()
	{
		return GasTags;
	}

	// 一种在编译阶段Get方法
	FORCEINLINE static FGameplayAbilityGlobalTags& GetPreConstruct()
	{
		if (!GasTags.InBattle.IsValid())
			GasTags.AddTags();
		
		return GasTags;
	}

private:

	static FGameplayAbilityGlobalTags GasTags;
};
