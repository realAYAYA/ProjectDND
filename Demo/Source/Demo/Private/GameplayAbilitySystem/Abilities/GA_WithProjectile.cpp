#include "GA_WithProjectile.h"

#include "AbilitySystemLog.h"
#include "Character/DCharacter.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DProjectile.h"

UGA_WithProjectile::UGA_WithProjectile()
{
	
}

void UGA_WithProjectile::ReceiveTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	CacheTargetData = TargetDataHandle;
	
	// Todo 检测数据合法性，取消技能
	// Todo 计算消耗 施加CD 抑或是因为法术反制施法失败，仍计算消耗，但不会施加效果
	// Todo 通知其它角色我要施法了

	bDoOnceAnimNotify = false;
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	MontageSetNextSectionName(FName("Loop"), FName("OnFire"));
}

void UGA_WithProjectile::OnReceiveAnimNotify(UDAbilitySystemComponent* Asc)
{
	if (!bDoOnceAnimNotify)
	{
		// Todo 法术施法成功进行结算，也可能被法术反制导致失败
		FireProjectile(CacheTargetData, Asc->GetOwner());
		
		bDoOnceAnimNotify = true;
	}
}

void UGA_WithProjectile::BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, UGA_WithProjectile* Ability, ADProjectile*& ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (!Ability || !Ability->IsInstantiated() || !Class.Get())
		return;

	auto* Character = GetDCharacter(*Ability->GetCurrentActorInfo());
	if (!Character || !Character->HasAuthority())
		return;
	
	ProjectileActor = nullptr;
	ProjectileActor = Character->GetWorld()->SpawnActorDeferred<ADProjectile>(*Class, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (IsValid(ProjectileActor))
	{
		ProjectileActor->InitializeProjectile(Ability, Character, TargetDataHandle);
	}
}

void UGA_WithProjectile::FinishSpawningProjectile(ADProjectile* ProjectileActor)
{
	if (IsValid(ProjectileActor))
	{
		ProjectileActor->FinishSpawning(FTransform());
	}
}

void UGA_WithProjectile::ApplyGameplayEffectToTarget(ADCharacter* Caster, ADCharacter* Target, ADProjectile* Projectile)
{
	// 30%可能被闪避(抵抗）
	if (FMath::RandRange(1, 10) > CalculateHitRate(Caster, Target) * 10)
	{
		// 目标闪避事件通知
		{
			const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_Dodge;
			FGameplayEventData Payload;
			Payload.EventTag = Tag;
			Payload.Instigator = Caster;
			Payload.Target = Target;
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
			Target->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
		}

		// 攻击被闪避事件通知
		{
			const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_BeingDodged;
			FGameplayEventData Payload;
			Payload.EventTag = Tag;
			Payload.Instigator = Caster;
			Payload.Target = Target;
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().RemoteHit);
			Caster->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
		}
		
		return;
	}
	
	// 构造GE Context
	FGameplayEffectContextHandle EffectContext = Caster->GetDAbilitySystemComponent()->MakeEffectContext();
	EffectContext.SetAbility(this);
	EffectContext.AddInstigator(Projectile, Caster);
	EffectContext.AddSourceObject(this);

	// 30%可能性暴击
	bool bCrit = FMath::RandRange(1, 10) <= CalculateHitRate(Caster, Target) * 10;
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
		Payload.Instigator = Caster;
		Payload.Target = Target;
		Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
		if (bCrit)
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().CritHit);
		Target->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}

	// 远程攻击命中目标事件通知
	{
		const FGameplayTag& Tag = FGameplayAbilityGlobalTags::Get().Event_Hit;
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = Caster;
		Payload.Target = Target;
		Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().MeleeHit);
		if (bCrit)
			Payload.InstigatorTags.AddTag(FGameplayAbilityGlobalTags::Get().CritHit);
		Caster->GetDAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}

	// 对目标施加GE
	for (TSubclassOf<UDGameplayEffect>& GameplayEffect : EffectsApplyToTarget)
	{
		if (!GameplayEffect.Get())
			continue;
		
		FGameplayEffectSpecHandle SpecHandle = Caster->GetDAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, Level, EffectContext);
		if (!SpecHandle.IsValid())
			continue;
		
		FActiveGameplayEffectHandle ActiveGEHandle = Target->GetDAbilitySystemComponent()->ApplyTurnBasedGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (!ActiveGEHandle.WasSuccessfullyApplied())
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Startup Effect %s"), *GetName(), *GetNameSafe(GameplayEffect));
	}
}

bool UGA_WithProjectile::FireProjectile_Implementation(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster)
{
	return true;
}
