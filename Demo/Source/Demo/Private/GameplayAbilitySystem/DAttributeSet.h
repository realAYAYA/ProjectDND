// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChange, float, V);


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class UDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	// -------------------------------------------------------------------------------
	//		Battle Properties
	// -------------------------------------------------------------------------------

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD", ReplicatedUsing = OnRep_MoveDistance)
	FGameplayAttributeData MoveDistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MoveDistance)
	
	UPROPERTY(BlueprintReadOnly, Category = "ProjectD", ReplicatedUsing = OnRep_MaxMoveDistance)
	FGameplayAttributeData MaxMoveDistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MaxMoveDistance)

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD", Replicated)
	FGameplayAttributeData MoveCost;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MoveCost)

	UPROPERTY(BlueprintReadOnly, Category = "ProjectD", ReplicatedUsing = OnRep_MaxMoveSpeed)
	FGameplayAttributeData MaxMoveSpeed;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MaxMoveSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Agility)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Spirit;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Spirit)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Stamina)
	
	
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData HealthRecovery;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, HealthRecovery)

	// 治疗量，比如致死打击可以造成治疗量的减少
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData HealRatio;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, HealRatio)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ManaRecovery;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ManaRecovery)


	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData MeleeAttackIntensity;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MeleeAttackIntensity)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData RangedAttackIntensity;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, RangedAttackIntensity)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, AttackSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData MagicIntensity;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MagicIntensity)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData HealIntensity;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, HealIntensity)
	
	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData PhyCriticalRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, PhyCriticalRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData MagicCriticalRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, MagicCriticalRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData HitRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, HitRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ArcaneDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ArcaneDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData FrostDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, FrostDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData FlameDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, FlameDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData NaturalDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, NaturalDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ShadowDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ShadowDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData DivineDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, DivineDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ParryRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ParryRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData DogeRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, DogeRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData BlockRate;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, BlockRate)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData PhyResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, PhyResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ArcaneResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ArcaneResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData FrostResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, FrostResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData FlameResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, FlameResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData ShadowResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, ShadowResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData NaturalResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, NaturalResist)

	UPROPERTY(BlueprintReadOnly, Category = "BaseAttributes")
	FGameplayAttributeData DivineResist;
	ATTRIBUTE_ACCESSORS(UDAttributeSet, DivineResist)

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnAttributeValueChange OnMoveDistanceChange;

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnAttributeValueChange OnMaxMoveDistanceChange;

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnAttributeValueChange OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "ProjectD")
	FOnAttributeValueChange OnMaxHealthChanged;
	
	
protected:

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_MaxMoveSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MoveDistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMoveDistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
};
