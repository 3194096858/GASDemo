#include "GameplayAbility/HitReactionAbility.h"

#include "Character/CharacterBase.h"
#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "DataAsset/CharacterDataAsset.h"

void UHitReactionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

int32 UHitReactionAbility::GetMontageNumber()
{
	UCharacterDataAsset* Asset = GetCharacterAsset();
	if (Asset == nullptr) return 0;


	return Asset->HitReactionMontageMap.Num();
}

UAnimMontage* UHitReactionAbility::GetMontage(const FGameplayTag& AttackDirectionTag)
{
	UCharacterDataAsset* Asset = GetCharacterAsset();
	if (Asset == nullptr) return 0;



	if (Asset->HitReactionMontageMap.Find(AttackDirectionTag) == nullptr) return nullptr;
	return *Asset->HitReactionMontageMap.Find(AttackDirectionTag);
}








