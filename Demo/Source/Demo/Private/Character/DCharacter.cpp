// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "AbilitySystemLog.h"
#include "DCharacterManager.h"
#include "DGameInstance.h"
#include "DPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
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

	AttributeSet = CreateDefaultSubobject<UDAttributeSet>(TEXT("AttributeSet"));
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMoveDistanceAttribute()).AddUObject(this, &ADCharacter::OnMoveDistanceChange);
}

void ADCharacter::BeginReplication()
{
	// Network & Replicated
	if (HasAuthority())
	{
		if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
		{
			RoleId = GameInstance->CharacterManager->GenerateRoleId();// 由服务器为角色下发唯一Id
			GameInstance->CharacterManager->RegisterCharacter(RoleId,this);
		}
	}

	Super::BeginReplication();
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
			GameInstance->CharacterManager->RegisterCharacter(RoleId,this);
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

void ADCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// PossessedBy()只在服务器执行
	InitCharacterData();
}

UAbilitySystemComponent* ADCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADCharacter::OnBattleBegin()
{
	K2_BattleBegin();
}

void ADCharacter::MyTurn()
{
	if (const auto* PS = GetPlayerState())
	{
		// Todo 确认控制权所属，控制器不一定正在控制角色
		if (auto* PC = Cast<ADPlayerController>(PS->GetPlayerController()))
		{
			PC->YourTurn(this);
		}
	}

	K2_MyTurn();
}

void ADCharacter::OnMoveDistanceChange(const FOnAttributeChangeData& Data) const
{
	if (Data.NewValue == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void ADCharacter::OnBattleEnd()
{
	K2_BattleEnd();
}

bool ADCharacter::InBattle() const
{
	return AbilitySystemComponent->HasMatchingGameplayTag(FGameplayAbilityGlobalTags::Get().InBattle);
}

void ADCharacter::OnRep_CharacterId()
{
	if (!HasAuthority())
	{
		if (const auto* GameInstance = Cast<UDGameInstance>(GetGameInstance()))
		{
			GameInstance->CharacterManager->UnRegisterCharacter(OldRoleId);// 移除旧信息
			GameInstance->CharacterManager->RegisterCharacter(RoleId,this);// 重新注册角色信息
			OldRoleId = RoleId;
		}
	}
}

void ADCharacter::OnRep_ControllerId()
{
}

void ADCharacter::InitCharacterData()
{
	if (!HasAuthority() || !AbilitySystemComponent || !IsValid(CharacterDataAsset))
		return;

	// Give abilities
	//AbilitySystemComponent->ClearAbility()
	for (const auto& AbilityClass : CharacterDataAsset->GasData.DefaultAbilities)
	{
		if (!AbilityClass)
			continue;
			
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(AbilityClass);
		const auto Handle = AbilitySystemComponent->GiveAbility(GameplayAbilitySpec);
		if (!Handle.IsValid())
		{
			ABILITY_LOG(Log, TEXT("Ability %s faild to apply Effect to Target %s"), *GetName(), *GetNameSafe(AbilityClass));
		}
	}

	// Apply gameplay effects
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	for (const auto& Effect : CharacterDataAsset->GasData.Effects)
	{
		if (!Effect.Get())
			continue;

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContextHandle);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ADCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	
	SharedParams.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, RoleId, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, ControllerId, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, bReadyTurnEnd, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
