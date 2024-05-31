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
	if (Asc->GetOwner()->HasAuthority())
	{
		// Todo 法术施法成功进行结算，也可能被法术反制导致失败
		
		FireProjectile(CacheTargetData, Asc->GetOwner());
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

bool UGA_WithProjectile::FireProjectile_Implementation(const FGameplayAbilityTargetDataHandle& TargetData, AActor* Caster)
{
	return true;
}
