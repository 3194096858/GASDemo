
#pragma once
#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS_AttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASDEMO2_API UGAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UGAS_AttributeSet();
protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;

public:
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Attack);
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Defense);


	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldData);

	
	
};
