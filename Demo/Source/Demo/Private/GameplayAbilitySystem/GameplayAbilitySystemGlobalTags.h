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
	FGameplayTag CritHit;// 承受暴击
	FGameplayTag MeleeHit;// 承受近战攻击
	FGameplayTag RemoteHit;// 承受远程攻击
	
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

		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.HostilityBehavior"), TEXT("ProjectD"));

		// 获得状态
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.GetEffect"), TEXT("ProjectD"));

		// 施加状态
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.GiveEffect"), TEXT("ProjectD"));

		// 角色受到攻击
		Event_TakeHit = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeHit"), TEXT("ProjectD"));
		// 命中对方
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.Hit"), TEXT("ProjectD"));

		// 受击类型
		MeleeHit = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.HitType.Melee"), TEXT("ProjectD"));
		RemoteHit = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.HitType.Remote"), TEXT("ProjectD"));
		CritHit = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.HitType.Crit"), TEXT("ProjectD"));
		
		// 角色受到伤害
		Event_TakeDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.TakeDamage"), TEXT("ProjectD"));
		
		// 角色受到任何控制
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bRooted"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bParalyzed"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Event.bRestricted.bSilenced"), TEXT("ProjectD"));

		// 是否为DeBuff
		Buff = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category1.Buff"), TEXT("ProjectD"));
		DeBuff = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.Category1.DeBuff"), TEXT("ProjectD"));

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
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Arc"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Frost"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Flame"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Divine"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Shadow"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Nature"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.DamageType.Mind"), TEXT("ProjectD"));

		// 全GE列表
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.List.Moving"), TEXT("ProjectD"));
		InBattle = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.List.InBattle"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.List.Casting"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.GE.List.Attacking"), TEXT("ProjectD"));

		// 按消耗技能分类
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.Action"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.Reaction"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category1.AdditionalAction"), TEXT("ProjectD"));

		// 专注技能
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Focus"), TEXT("ProjectD"));

		// 是否为法术（或战技）
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Combat"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell"), TEXT("ProjectD"));
		
		// 各职业流派
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Frost"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Flame"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Arc"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Divine"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Shadow"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Nature"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.Category2.Spell.Mind"), TEXT("ProjectD"));

		// 全技能列表
		Move = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.List.Move"), TEXT("ProjectD"));
		UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GAS.Ability.List.MoveInBattle"), TEXT("ProjectD"));
	}

	bool IsBuff(const FGameplayTagContainer& Tags, const bool bDeBuff = false) const
	{
		for (const auto& Tag : Tags)
		{
			if (!bDeBuff && Tag == Buff)
				return true;

			if (bDeBuff && Tag == DeBuff)
				return true;
		}
		
		return false;
	}
	
	bool CheckHitWithDistance(const FGameplayTagContainer& Tags, const bool bMelee) const
	{
		for (const auto& Tag : Tags)
		{
			if (!bMelee && Tag == RemoteHit)
				return true;

			if (bMelee && Tag == MeleeHit)
				return true;
		}
		
		return false;
	}
	
	bool IsCriticalHit(const FGameplayTagContainer& Tags) const
	{
		for (const auto& Tag : Tags)
			if (Tag == CritHit)
				return true;
		
		return false;
	}

	FORCEINLINE static const FGameplayAbilityGlobalTags& Get()
	{
		return GasTags;
	}

	// 一种在编译阶段Get方法(构造函数中调用）
	FORCEINLINE static FGameplayAbilityGlobalTags& GetPreConstruct()
	{
		if (!GasTags.InBattle.IsValid())
			GasTags.AddTags();
		
		return GasTags;
	}

private:

	static FGameplayAbilityGlobalTags GasTags;
};
