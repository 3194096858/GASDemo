

#include "GameplayEffectExecutionCalculation/DamageEffectExecutionCalculation.h"

#include "AttributeSet/GAS_AttributeSet.h"


UDamageEffectExecutionCalculation::UDamageEffectExecutionCalculation()
{
	FProperty* HealthProperty = FindFieldChecked<FProperty>(UGAS_AttributeSet::StaticClass(),TEXT("Health"));
	FProperty* AttackProperty = FindFieldChecked<FProperty>(UGAS_AttributeSet::StaticClass(), TEXT("Attack"));
	FProperty* StrengthProperty = FindFieldChecked<FProperty>(UGAS_AttributeSet::StaticClass(), TEXT("Strength"));
	FProperty* TargetDefenseProperty = FindFieldChecked<FProperty>(UGAS_AttributeSet::StaticClass(), TEXT("Defense"));
	
	FGameplayEffectAttributeCaptureDefinition HealthAttributeCaptureDefinition = FGameplayEffectAttributeCaptureDefinition(HealthProperty,EGameplayEffectAttributeCaptureSource::Source,true);
	FGameplayEffectAttributeCaptureDefinition AttackAttributeCaptureDefinition = FGameplayEffectAttributeCaptureDefinition(AttackProperty, EGameplayEffectAttributeCaptureSource::Source, true);
	FGameplayEffectAttributeCaptureDefinition StrengthAttributeCaptureDefinition = FGameplayEffectAttributeCaptureDefinition(StrengthProperty, EGameplayEffectAttributeCaptureSource::Source, true);
	FGameplayEffectAttributeCaptureDefinition TargetDefenseAttributeCaptureDefinition = FGameplayEffectAttributeCaptureDefinition(TargetDefenseProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	this->RelevantAttributesToCapture.Add(HealthAttributeCaptureDefinition);
	this->RelevantAttributesToCapture.Add(AttackAttributeCaptureDefinition);
	this->RelevantAttributesToCapture.Add(StrengthAttributeCaptureDefinition);
	this->RelevantAttributesToCapture.Add(TargetDefenseAttributeCaptureDefinition);

}





void UDamageEffectExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	if (RelevantAttributesToCapture.Num() == 0) return;

	float Attack = 0.0f;
	float Strength = 0.0f;
	float TargetDefense = 0.0f;
	float TotalDamage = 0.0f;
	FGameplayModifierEvaluatedData ModifierData;
	FAggregatorEvaluateParameters EvaluateParameters;
	ModifierData.Attribute = this->RelevantAttributesToCapture[0].AttributeToCapture;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(this->RelevantAttributesToCapture[1], EvaluateParameters, Attack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(this->RelevantAttributesToCapture[2], EvaluateParameters, Strength);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(this->RelevantAttributesToCapture[3], EvaluateParameters, TargetDefense);


	TotalDamage = Attack * ((1 + Strength * 0.01f) / (1 + TargetDefense * 0.01f));
	ModifierData.Magnitude = ModifierData.Magnitude - TotalDamage;

	OutExecutionOutput.AddOutputModifier(ModifierData);

}