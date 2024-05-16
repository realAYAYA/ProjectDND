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
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bRooted"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bParalyzed"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bSilenced"), TEXT("ProjectD"));
		
		Event_TakeDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage"), TEXT("ProjectD"));

		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category1.Buff"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category1.DeBuff"), TEXT("ProjectD"));

		// Buff类型
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category2.None"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category2.Magic"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category2.Curse"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category2.Disease"), TEXT("ProjectD"));

		// 限制类buff标签
		Paralysis = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Paralysis"), TEXT("ProjectD"));
		Stun	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Paralysis.Stun"), TEXT("ProjectD"));
		Sleep	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Paralysis.Sleep"), TEXT("ProjectD"));
		Fear	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Paralysis.Fear"), TEXT("ProjectD"));
		Root	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Root"), TEXT("ProjectD"));
		Silence	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Restrict.Silence"), TEXT("ProjectD"));

		// 伤害类标签
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Phy"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Arc"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Frost"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Flame"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Divine"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Shadow"), TEXT("ProjectD"));
		//UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Nature"), TEXT("ProjectD"));

		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.Action"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.Reaction"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.AdditionalAction"), TEXT("ProjectD"));

		// 专注技能
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Focus"), TEXT("ProjectD"));

		
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Combat"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell"), TEXT("ProjectD"));

		// 各职业三系流派
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Frost"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Flame"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Arc"), TEXT("ProjectD"));
		
		Move = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category.Movement.Move"), TEXT("ProjectD"));

		InBattle	= UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.State.InBattle"), TEXT("ProjectD"));
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
