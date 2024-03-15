#include "GE_Move.h"
#include "GameplayAbilitySystem/DAttributeSet.h"
#include "GMMC/GMMC_MoveCost.h"

UGE_Move::UGE_Move()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	
	Period.SetValue(0.1);

	FCustomCalculationBasedFloat CustomCalculation;
	CustomCalculation.CalculationClassMagnitude = UGMMC_MoveCost::StaticClass();

	FGameplayModifierInfo Info;
	Info.Attribute = UDAttributeSet::GetMoveDistanceAttribute();
	Info.ModifierOp = EGameplayModOp::Additive;
	Info.ModifierMagnitude = FGameplayEffectModifierMagnitude(CustomCalculation);
	this->Modifiers.Add(Info);
}
