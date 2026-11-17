

#include "Component/GAS_AbilitySystemComponent.h"
#include "GameplayTag/GameplayTag.h"

void UGAS_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag::Ability::Passive) == true)
	{
		TryActivateAbility(AbilitySpec.Handle);
		//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("OnGiveAbility: Passive ")));

	}
	//AbilitySpec.Ability->AbilityTags.
	//AbilitySpec.

}

void UGAS_AbilitySystemComponent::ActivateAbility(const FGameplayTag& AbilityTag)
{

	TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
	//Cancel

}
