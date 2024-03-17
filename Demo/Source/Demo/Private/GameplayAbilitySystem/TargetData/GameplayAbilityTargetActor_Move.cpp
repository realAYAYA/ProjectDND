// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityTargetActor_Move.h"
#include "Abilities/GameplayAbility.h"

void AGameplayAbilityTargetActor_Move::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	
}

void AGameplayAbilityTargetActor_Move::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();

	// Todo 寻找鼠标点击位置，并调用网络接口发送数据
	if (!HasAuthority())
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
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
	}
}
