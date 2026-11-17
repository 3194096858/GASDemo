

#include "GameplayAbility/GameplayAbilityBase.h"
#include "Character/CharacterBase.h"
#include "Controller/PlayerController/GAS_PlayerController.h"

#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "DataAsset/CharacterDataAsset.h"

UGameplayAbilityBase::UGameplayAbilityBase()
{

	//AbilityTags.Ad
}

void UGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


}



ACharacterBase* UGameplayAbilityBase::GetCharacter()
{
	return Cast<ACharacterBase>(GetAvatarActorFromActorInfo());

}

AGAS_PlayerController* UGameplayAbilityBase::GetPlayerController()
{
	return Cast<AGAS_PlayerController>(GetCharacter()->GetController());

}

UGAS_GameInstance* UGameplayAbilityBase::GetGameInstance()
{
	return Cast<UGAS_GameInstance>(GetCharacter()->GetGameInstance());


}

UObject* UGameplayAbilityBase::GetAssetObject()
{
	if (this->CharacterDataAsset.IsNull() == true) return nullptr;
	UObject* Asset = GetGameInstance()->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());

	return Asset;
}

UCharacterDataAsset* UGameplayAbilityBase::GetCharacterAsset()
{
	return Cast<UCharacterDataAsset>(GetAssetObject());

}
