// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DCharacterManager.h"
#include "DGameInstance.h"
#include "DPlayerController.h"
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

void ADCharacter::BeginReplication()
{
	Super::BeginReplication();

	// Network & Replicated
	if (HasAuthority())
	{
		if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
		{
			ReplicatedRoleId = GameInstance->CharacterManager->GenerateRoleId();// 由服务器为角色下发唯一Id
			GameInstance->CharacterManager->RegisterCharacter(ReplicatedRoleId,this);
		}
	}
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADCharacter::PostNetInit()
{
	if (!HasAuthority())
	{
		// 注册自己的信息
		if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
		{
			GameInstance->CharacterManager->RegisterCharacter(ReplicatedRoleId,this);
		}
	}
	
	Super::PostNetInit();
}

void ADCharacter::BeginDestroy()
{
	/*if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
	{
		GameInstance->CharacterManager->RegisterCharacter(ReplicatedRoleId,this);
	}*/
	
	Super::BeginDestroy();
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADCharacter::SetBattleInstance(ATurnBasedBattleInstance* In)
{
	BattleInstance = In;
	
#if !UE_SERVER // 如果不是以DS编译，而是以Listening Server启动方式时，OnRep不会在主机上调用，需要手动触发
	if (HasAuthority())
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

void ADCharacter::OnBattleEnd_Implementation()
{
}

void ADCharacter::OnCharacterIdChange()
{
	if (!HasAuthority())
	{
		if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
		{
			GameInstance->CharacterManager->UnRegisterCharacter(OldRoleId);// 移除旧信息
			GameInstance->CharacterManager->RegisterCharacter(ReplicatedRoleId,this);// 重新注册角色信息
			OldRoleId = ReplicatedRoleId;
		}
	}
}

void ADCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, BattleInstance, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, ReplicatedRoleId, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
