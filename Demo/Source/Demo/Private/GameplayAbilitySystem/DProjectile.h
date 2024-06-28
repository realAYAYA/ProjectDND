﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameFramework/Actor.h"
#include "DProjectile.generated.h"

class UGA_WithProjectile;
class ADCharacter;

// 自定义投射物参数集，网络同步消息通用结构
USTRUCT(BlueprintType)
struct FProjectileParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectD")
	int32 D1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectD")
	int32 D2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectD")
	int64 N1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectD")
	int64 N2;

	UPROPERTY(EditAnywhere, Category = "ProjectD")
	TArray<AActor*> Actors;
};

UCLASS()
class ADProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectD")
	class USphereComponent* CollisionComp;
	
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectD", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
	
	// Sets default values for this actor's properties
	ADProjectile(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "ProjectD")
	void InitializeProjectile(UGA_WithProjectile* InAbility, ADCharacter* InCaster, const FGameplayAbilityTargetDataHandle& InTargetData);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "ProjectD")
	float LifeSpanAfterActivate = 8;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	ADCharacter* Caster;
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD")
	UGA_WithProjectile* AbilityInstance;

	// 投射物激活，服务器专用
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ProjectD")
	void Server_Activate(const FProjectileParams& Params);

	// 投射物激活，执行在服务器或主机端
	UFUNCTION(BlueprintNativeEvent, Category = "ProjectD")
	bool ReceiveOnActivateServerOnly(const FProjectileParams& Params);
	
	// 激活表现，广播用
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_Activate(const FProjectileParams& Params);

	// 激活函数，网络广播
	UFUNCTION(BlueprintNativeEvent, Category = "ProjectD")
	bool ReceiveOnActivateNetMulticast(const FProjectileParams& Params);
};
