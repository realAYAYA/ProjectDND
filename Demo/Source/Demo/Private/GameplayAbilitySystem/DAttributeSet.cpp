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
		SetMoveDistance(FMath::Clamp(GetMoveDistance(), 0.0f, GetMaxMoveDistance()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMoveDistanceAttribute())
	{
		SetMaxMoveDistance(FMath::Clamp(GetMaxMoveDistance(), 0.0f, 100000));
	}
	else if (Data.EvaluatedData.Attribute == GetMoveCostAttribute())
	{
		SetMoveCost(FMath::Clamp(GetMoveCost(), 1, 10));
	}
}

void UDAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MoveDistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxMoveDistance, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MoveCost, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxMoveSpeed, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
