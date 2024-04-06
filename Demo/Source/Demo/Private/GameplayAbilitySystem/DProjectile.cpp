// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectile.h"
#include "Character/DCharacter.h"

#include "AbilitySystemComponent.h"
#include "DAbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADProjectile::ADProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bReplicates = true;
	//SetReplicatingMovement(true);
	
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADProjectile::OnHit);// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 500.f;// Todo 初速由设计人员定制
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}

void ADProjectile::Initialize(ADCharacter* InCaster, ADCharacter* InTarget)
{
	if (!HasAuthority())
		return;
	
	Caster = InCaster;
	Target = InTarget;

	if (Caster)
		CollisionComp->IgnoreActorWhenMoving(Caster, true);
}

void ADProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
 {
	// Only add impulse and destroy projectile if we hit a physics
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		ADCharacter* Character = Cast<ADCharacter>(OtherActor);
		if (HasAuthority() && Character)
		{
			// 施加效果
			for (const TSubclassOf<UGameplayEffect>& Effect : Effects)
			{
				FGameplayEffectContextHandle EffectContextHandle = Character->GetDAbilitySystemComponent()->MakeEffectContext();
				EffectContextHandle.AddSourceObject(Character);
				//Character->ApplyGameplayEffectToSelf(Effect, EffectContextHandle);
			}

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ADProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

