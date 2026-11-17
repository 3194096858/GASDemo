
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GAS_AbilitySystemGlobals.generated.h"




UCLASS()
class GASDEMO2_API UGAS_AbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
protected:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;






	
};
