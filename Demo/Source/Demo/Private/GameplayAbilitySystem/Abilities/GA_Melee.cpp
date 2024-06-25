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
	// Todo 施加近战攻击效果
	// Todo 可能被闪避

	// 30%可能性未命中
	if (FMath::RandRange(1, 10) > 7)
	{
		ReceiveHitTarget(CacheTargetData, Asc->GetOwner());
		return;
	}

	// 30%可能性暴击
	bool bCrit = FMath::RandRange(1, 10) > 7;
	

	// 施加命中GE
	FGameplayEffectContextHandle EffectContext = Asc->MakeEffectContext();
	EffectContext.SetAbility(this);
	EffectContext.AddInstigator(CurrentActorInfo->AvatarActor.Get(), CurrentActorInfo->AvatarActor.Get());
	EffectContext.AddSourceObject(this);

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

	if (const ADCharacter* Target = Cast<ADCharacter>(ParseOneTargetTargetData(CacheTargetData)))
	{
		for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsJustApplyOnStart)
		{
			if (!GameplayEffect.Get())
				continue;
		
			FGameplayEffectSpecHandle SpecHandle = Asc->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
			if (!SpecHandle.IsValid())
				continue;

			SpecHandle.Data->CapturedSourceTags;
		
			FActiveGameplayEffectHandle ActiveGEHandle = Target->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			if (!ActiveGEHandle.WasSuccessfullyApplied())
				ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
		}
	}

	ReceiveHitTarget(CacheTargetData, Asc->GetOwner());
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
