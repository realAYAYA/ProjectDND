#include "GMMC_MoveCost.h"

#include "GameplayAbilitySystem/DAttributeSet.h"

UGMMC_MoveCost::UGMMC_MoveCost()
{
	//ManaDef defined in header FGameplayEffectAttributeCaptureDefinition ManaDef;
	MoveCost.AttributeToCapture = UDAttributeSet::GetMoveDistanceAttribute();
	MoveCost.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MoveCost.bSnapshot = false;

	RelevantAttributesToCapture.Add(MoveCost);
}

float UGMMC_MoveCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from the source and target as that can affect which buffs should be used
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	float MoveCostValue = 0.f;
	GetCapturedAttributeMagnitude(MoveCost, Spec, EvaluationParameters, MoveCostValue);
	MoveCostValue = FMath::Max<float>(MoveCostValue, 0.0f);
	
	return -1;
}
