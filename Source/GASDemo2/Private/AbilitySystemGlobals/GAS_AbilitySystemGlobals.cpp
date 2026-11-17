

#include "AbilitySystemGlobals/GAS_AbilitySystemGlobals.h"
#include "Struct/GAS_GameplayEffectContext.h"


FGameplayEffectContext* UGAS_AbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FGAS_GameplayEffectContext();
}
