// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DPlayerController.h"
#include "TurnBasedBattleInstance.h"
#include "GameFramework/PlayerState.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Gameplay Ability System
	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADCharacter::SetBattleInstance(ATurnBasedBattleInstance* In)
{
	BattleInstance = In;
	
#if !UE_SERVER // 如果不是以DS编译，而是以Listening Server启动方式时，OnRep不会在主机上调用，需要手动触发
	if (GetNetMode() != NM_Client)
	{
		OnBattleInstance();
	}
#endif
}

void ADCharacter::OnBattleInstance()
{
	K2_OnBattleInstance();
}

void ADCharacter::NotifyYourTurn_Implementation()
{
}

void ADCharacter::YourTurn()
{
	if (const auto* PS = GetPlayerState())
	{
		if (auto* PC = Cast<ADPlayerController>(PS->GetPlayerController()))
		{
			PC->YourTurn(this);
		}
	}
}

void ADCharacter::ReqTurnEnd()
{
	if (BattleInstance)
		BattleInstance->ReqTurnEnd(this);
}

void ADCharacter::OnBattleEnd_Implementation()
{
}

void ADCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, BattleInstance, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
