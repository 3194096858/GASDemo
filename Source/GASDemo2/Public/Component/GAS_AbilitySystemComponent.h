
#pragma once



#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS_AbilitySystemComponent.generated.h"



struct FGameplayTag;


UCLASS()
class GASDEMO2_API UGAS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;


public:

public:
	void ActivateAbility(const FGameplayTag& AbilityTag);
	/*
	UFUNCTION(Server,Reliable)
	void ActivateAbility(const FGameplayTag& AbilityTag);
*/


};
