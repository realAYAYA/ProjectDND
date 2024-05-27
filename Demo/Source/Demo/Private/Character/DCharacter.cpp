// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "DPlayerController.h"
#include "GameplayAbilitySystem/DAbilitySystemComponent.h"
#include "GameplayAbilitySystem/DAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemLog.h"
#include "TurnBasedBattleInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"

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
	RoleId = GenerateRoleId();// 由服务器为角色下发唯一Id
	RegisterCharacter(RoleId,this);

	Super::BeginReplication();
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADCharacter::PostNetInit()
{
	RegisterCharacter(RoleId,this);
	
	Super::PostNetInit();
}

void ADCharacter::BeginDestroy()
{
	UnRegisterCharacter(this->RoleId);
	
	Super::BeginDestroy();
}

void ADCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// PossessedBy()只在服务器执行
	Server_InitCharacterData();
}

UAbilitySystemComponent* ADCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADCharacter::OnBattleBegin(ATurnBasedBattleInstance* In)
{
	BattleInstance = In;

	// 通知到PC
	if (auto* PC = Cast<ADPlayerController>(Controller))
	{
		if (IsLocallyControlled())
			PC->K2_BattleBegin(this);// 通知用户进入战斗（战斗界面, 操作模式变更）
	}

	K2_BattleBegin();
}

void ADCharacter::Client_MyTurn()
{
	// 玩家正在控制该角色，通知到PC
	if (auto* PC = Cast<ADPlayerController>(Controller))
	{
		if (IsLocallyControlled())
			PC->Client_MyTurn(this);
	}
	else
	{
		/*// 检查该角色的控制权归属是否为本地PC
		PC = Cast<ADPlayerController>(GetWorld()->GetFirstPlayerController());
		if (!PC || PC->PlayerId == ControllerId)
			return;// 该角色的控制权非本地控制

		// 检查本地PC是否在对回合中的角色进行控制，如果没有角色或角色没有处于活动回合，就通知到PC(自动切换镜头以及角色控制等等)
		const auto* C = Cast<ADCharacter>(PC->GetPawn());
		if (!C || !C->IsMyTurn())
			return;

		if (PC->IsLocalController())
			PC->Client_MyTurn(this);*/
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

bool ADCharacter::IsMyTurn() const
{
	if (BattleInstance)
		return BattleInstance->IsMyTurn(this);

	return false;
}

void ADCharacter::OnRep_CharacterId()
{
	UnRegisterCharacter(OldRoleId);// 移除旧信息
	RegisterCharacter(RoleId,this);// 重新注册角色信息
	OldRoleId = RoleId;
}

void ADCharacter::OnRep_ControllerId()
{
}

void ADCharacter::Server_InitCharacterData()
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

static int64 SerialNum = 0;
static TMap<int64, ADCharacter*> CharacterMap;

ADCharacter* ADCharacter::SearchCharacterWithId(const int64 Id)
{
	if (const auto* Ptr = CharacterMap.Find(Id))
		return *Ptr;

	return nullptr;
}

void ADCharacter::RegisterCharacter(const int64 Id, ADCharacter* In)
{
	if (CharacterMap.Contains(Id))
	{
		*CharacterMap.Find(Id) = In;
		return;
	}
	
	CharacterMap.Add(Id, In);
}

void ADCharacter::UnRegisterCharacter(const int64 Id)
{
	CharacterMap.Remove(Id);
	if (CharacterMap.Num() == 0) SerialNum = 0;// 重置Id生成器
}


int64 ADCharacter::GenerateRoleId()
{
	return ++SerialNum;
}

void ADCharacter::Foreach(const TFunction<bool(ADCharacter*)>& InFunc)
{
	for (const auto T : CharacterMap)
	{
		if (T.Value)
		{
			if (!InFunc(T.Value))
				return;
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
	DOREPLIFETIME_WITH_PARAMS_FAST(ADCharacter, CharacterName, SharedParams);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
