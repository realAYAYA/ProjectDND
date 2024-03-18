// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityTargetActor_Move.h"
#include "Abilities/GameplayAbility.h"

AGameplayAbilityTargetActor_Move::AGameplayAbilityTargetActor_Move(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	ShouldProduceTargetDataOnServer = false;
	bDebug = false;
	bDestroyOnConfirmation = true;

	bReplicates = true;
}

void AGameplayAbilityTargetActor_Move::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		PrimaryPC = GetWorld()->GetFirstPlayerController();
		ConfirmTargeting();
	}
}

void AGameplayAbilityTargetActor_Move::ConfirmTargetingAndContinue()
{
	APlayerController* PC = PrimaryPC.Get();
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC);
	bool bHit = false;
	FHitResult HitResult;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			bHit = PC->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, false, HitResult);
		}
	}

	if (bHit)
	{
		const FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromHitResult(OwningAbility.Get(), HitResult);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
}
