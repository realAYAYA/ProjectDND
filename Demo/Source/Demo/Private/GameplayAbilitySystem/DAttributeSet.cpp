// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

void UDAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMoveSpeedAttribute())
	{
		const ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
		if (UCharacterMovementComponent* CharacterMovement = OwningCharacter->GetCharacterMovement())
		{
			CharacterMovement->MaxWalkSpeed = GetMaxMoveSpeed();
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMoveDistanceAttribute())
	{
		SetMoveDistance(FMath::Clamp(GetMoveDistance(), 0.0f, GetMoveDistance()));
	}
}

void UDAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxMoveSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, Mana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxMana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, Energy, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxEnergy, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, Rage, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxRage, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, CastSpeed, COND_None, REPNOTIFY_OnChanged);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


void UDAttributeSet::OnRep_MaxMoveSpeed(const FGameplayAttributeData& OldMaxMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, MaxMoveSpeed, OldMaxMoveSpeed);
}

void UDAttributeSet::OnRep_MoveDistance(const FGameplayAttributeData& OldMoveDistanced)
{
	
}

void UDAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, Mana, OldMana);
	OnManaChanged.Broadcast(GetMana());
}

void UDAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, MaxMana, OldMaxMana);
	OnMaxManaChanged.Broadcast(GetMaxMana());
}

void UDAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, Energy, OldEnergy);
	OnEnergyChanged.Broadcast(GetEnergy());
}

void UDAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, MaxEnergy, OldMaxEnergy);
	OnMaxEnergyChanged.Broadcast(GetMaxEnergy());
}

void UDAttributeSet::OnRep_Rage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, Rage, OldRage);
	OnRageChanged.Broadcast(GetRage());
}

void UDAttributeSet::OnRep_MaxRage(const FGameplayAttributeData& OldMaxRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, MaxRage, OldMaxRage);
	OnMaxRageChanged.Broadcast(GetMaxRage());
}

void UDAttributeSet::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, CastSpeed, OldCastSpeed);
}

void UDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHeath)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, Health, OldHeath);
	OnHealthChanged.Broadcast(GetHealth());
}

void UDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHeath)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet, MaxHealth, OldMaxHeath);
	OnMaxHealthChanged.Broadcast(GetMaxHealth());
}