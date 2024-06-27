#include "GA_Melee.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"

#include "AbilitySystemLog.h"

UGA_Melee::UGA_Melee()
{
}

void UGA_Melee::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;

	// Todo 检测数据合法性，取消技能
	// Todo 计算消耗 施加CD
	// Todo 通知其它角色我要施法了，近战技能可能会被招架
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	MontageSetNextSectionName(FName("Loop"), FName("OnCut"));
}

void UGA_Melee::OnReceiveAnimNotify(UDAbilitySystemComponent* Asc)
{
	const ADCharacter* Target = Cast<ADCharacter>(ParseOneTargetTargetData(CacheTargetData));
	if (!Target)
	{
		ABILITY_LOG(Warning, TEXT("Ability %s error, no target"), *GetName());
		return;
	}
	
	// 30%可能被闪避
	if (FMath::RandRange(1, 10) > CalculateHitRate(GetDCharacter(*CurrentActorInfo), Target) * 10)
	{
		// 目标闪避事件通知
		{
			const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_Dodge;
			FGameplayEventData Payload;
			Payload.EventTag = Tag;
			Payload.Instigator = CurrentActorInfo->AvatarActor.Get();
			Payload.Target = Target;
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
			Target->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
		}

		// 攻击被闪避事件通知
		{
			const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_BeingDodged;
			FGameplayEventData Payload;
			Payload.EventTag = Tag;
			Payload.Instigator = CurrentActorInfo->AvatarActor.Get();
			Payload.Target = Target;
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
			Asc->HandleGameplayEvent(Tag, &Payload);
		}
		
		ReceiveHitTarget(CacheTargetData, Asc->GetOwner());
		return;
	}
	
	// 构造GE Context
	FGameplayEffectContextHandle EffectContext = Asc->MakeEffectContext();
	EffectContext.SetAbility(this);
	EffectContext.AddInstigator(CurrentActorInfo->AvatarActor.Get(), CurrentActorInfo->AvatarActor.Get());
	EffectContext.AddSourceObject(this);

	// 30%可能性暴击
	bool bCrit = FMath::RandRange(1, 10) <= CalculateHitRate(GetDCharacter(*CurrentActorInfo), Target) * 10;
	if (bCrit)
	{
		// Todo 我们可以不用自己拓展新的参数，而是使用自带的参数解析成自己的
		FHitResult CritParams;
		CritParams.bBlockingHit;
		CritParams.Distance;
		CritParams.Location;
		CritParams.MyItem;
		CritParams.Time;
		EffectContext.AddHitResult(CritParams);
	}

	// 目标受到攻击事件通知
	{
		const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_TakeHit;
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = CurrentActorInfo->AvatarActor.Get();
		Payload.Target = Target;
		Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
		if (bCrit)
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().CritHit);
		Target->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}

	// 近战攻击命中目标事件通知
	{
		const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_Hit;
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = CurrentActorInfo->AvatarActor.Get();
		Payload.Target = Target;
		Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
		if (bCrit)
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().CritHit);
		Asc->HandleGameplayEvent(Tag, &Payload);
	}

	// 对目标施加GE
	for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsApplyToTarget)
	{
		if (!GameplayEffect.Get())
			continue;
		
		FGameplayEffectSpecHandle SpecHandle = Asc->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
		if (!SpecHandle.IsValid())
			continue;
		
		FActiveGameplayEffectHandle ActiveGEHandle = Target->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (!ActiveGEHandle.WasSuccessfullyApplied())
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
	}
	
	ReceiveHitTarget(CacheTargetData, Asc->GetOwner());
}

float UGA_Melee::CalculateHitRate(const ADCharacter* Caster, const ADCharacter* Target)
{
	if (!Target)
		return 0.0f;
	
	return 0.7f;
}

float UGA_Melee::CalculateCritRate(const ADCharacter* Caster, const ADCharacter* Target)
{
	return 0.3f;
}

bool UGA_Melee::ReceiveHitTarget_Implementation(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster)
{
	
	/*for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsJustApplyOnStart)
	{
		if (!GameplayEffect.Get())
			continue;
		
		const FGameplayEffectSpecHandle SpecHandle = Asc->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
		if (!SpecHandle.IsValid())
			continue;
		
		FActiveGameplayEffectHandle ActiveGEHandle = Asc->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (!ActiveGEHandle.WasSuccessfullyApplied())
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
	}
	*/
	
	return false;
}
