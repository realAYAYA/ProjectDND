// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

class UGA_WithProjectile;
class ADCharacter;

UCLASS()
class ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;
	
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectM, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
	
	// Sets default values for this actor's properties
	ADProjectile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void InitializeProjectile(UGA_WithProjectile* InAbility, ADCharacter* InCaster, const FGameplayAbilityTargetDataHandle& InTargetData);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	float LifeSpanAfterExp;

	// 投射物爆炸
	UFUNCTION(NetMulticast, Reliable)
	void Server_Detonate();

	// 蓝图处理投射物爆炸表现
	UFUNCTION(BlueprintNativeEvent, Category = "ProjectD")
	bool ReceiveDetonate();
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	ADCharacter* Caster;

	// 如果Target为空，有可能是对应技能采用的是坐标位置作为目标
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY()
	UGA_WithProjectile* AbilityInstance;

	//void ApplyGameplayEffectToTarget(AActor* Target);

protected:
	
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
};
