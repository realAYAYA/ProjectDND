﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	ADProjectile();

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void Initialize(ADCharacter* InCaster, ADCharacter* InTarget, UGA_WithProjectile* InAbility);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY()
	AActor* Caster;

	UPROPERTY()
	AActor* Target;

	UPROPERTY()
	FVector TargetLocation;// 如果目标丢失，则销毁在最后出现的位置

	UPROPERTY()
	UGA_WithProjectile* AbilityInstance;

	//void ApplyGameplayEffectToTarget(AActor* Target);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns ProjectileMovement sub-object **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
