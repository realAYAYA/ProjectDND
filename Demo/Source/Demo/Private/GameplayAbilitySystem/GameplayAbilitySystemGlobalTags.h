#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

// 适合添加预设的Gas相关Tags
struct DEMO_API FGameplayAbilityGlobalTags final : public FGameplayTagNativeAdder
{
	FGameplayTag InBattle;
	
	// 机制类GameplayTag
	FGameplayTag Event_BattleBegin;
	FGameplayTag Event_BattleEnd;
	FGameplayTag Event_MyTurn;
	FGameplayTag Event_Hostility;// 敌对行为（例如，对中立目标进行攻击）

	FGameplayTag Event_TakeHit;
	FGameplayTag Event_TakeDamage;

	// 能显示在玩家界面的GE标签
	
	FGameplayTag Buff;
	FGameplayTag DeBuff;
	
	FGameplayTag Paralysis;
	FGameplayTag Stun;
	FGameplayTag Sleep;
	FGameplayTag Fear;

	FGameplayTag Root;
	
	FGameplayTag Silence;
	
	// 行为标签
	
	FGameplayTag Move;
	
	virtual void AddTags() override
	{
		if (GasTags.InBattle.IsValid())
			return;

		Event_BattleBegin = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.BattleBegin"), TEXT("ProjectD"));
		Event_BattleEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.BattleEnd"), TEXT("ProjectD"));
		Event_MyTurn = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.MyTurn"), TEXT("ProjectD"));
		Event_Hostility = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.HostilityBehavior"), TEXT("ProjectD"));
		
		Event_TakeHit = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit.Phy"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit.Mag"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit.Melee"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit.Remote"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit.Crit"), TEXT("ProjectD"));
		
		Event_TakeDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Phy"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Arc"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Frost"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Flame"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Divine"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Shadow"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage.Nature"), TEXT("ProjectD"));

		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category.Buff"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category.DeBuff"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category.Limit"), TEXT("ProjectD"));
		
		InBattle	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.InBattle"), TEXT("ProjectD"));
		
		Paralysis	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis"), TEXT("ProjectD"));
		Stun		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Stun"), TEXT("ProjectD"));
		Sleep		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Sleep"), TEXT("ProjectD"));
		Fear		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Paralysis.Fear"), TEXT("ProjectD"));

		Root		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Root"), TEXT("ProjectD"));
		Silence		= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Limit.Silence"), TEXT("ProjectD"));

		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Action"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Reaction"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.AdditionalAction"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Combat"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Spell"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Class.Mage"), TEXT("ProjectD"));
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
