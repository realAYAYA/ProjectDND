#include "GA_WithProjectile.h"

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
	
	// 收到来自客户端的数据，进行最终施法(攻击)流程
	MontageSetNextSectionName(FName("Loop"), FName("OnFire"));
}

void UGA_WithProjectile::OnReceiveAnimNotify(UDAbilitySystemComponent* Asc)
{
	// 程序运行到该函数时不能保证Ability存有正确的Asc或Actor信息
	// Todo 法术施法成功进行结算，也可能被法术反制导致失败
	
	K2_FireProjectile(CacheTargetData, Asc->GetOwner());
}

void UGA_WithProjectile::BeginSpawningProjectile(const TSubclassOf<ADProjectile>& Class, ADProjectile*& ProjectileActor)
{
	ProjectileActor = nullptr;
	
	if (UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (*Class != nullptr)
			ProjectileActor = World->SpawnActorDeferred<ADProjectile>(*Class, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	}

	if (ProjectileActor)
	{
		ProjectileActor->AbilityInstance = this;
	}
}

void UGA_WithProjectile::FinishSpawningProjectile(ADProjectile* ProjectileActor, const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (IsValid(ProjectileActor))
	{
		auto* Caster = Cast<ADCharacter>(this->GetDAbilitySystemComponent(CurrentActorInfo)->GetOwner());
		ProjectileActor->InitializeProjectile(this, Caster, TargetDataHandle);
		ProjectileActor->FinishSpawning(FTransform());
	}
}
