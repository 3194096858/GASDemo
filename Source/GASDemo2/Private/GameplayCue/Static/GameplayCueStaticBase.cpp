

#include "GameplayCue/Static/GameplayCueStaticBase.h"

#include "Character/CharacterBase.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/CharacterDataAsset.h"
#include "AssetManager/GAS_AssetManager.h"


void UGameplayCueStaticBase::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	
	Super::HandleGameplayCue(MyTarget,EventType,Parameters);
	this->Character = Cast<ACharacterBase>(MyTarget);


}




ACharacterBase* UGameplayCueStaticBase::GetCharacter()
{
	return this->Character;
}


UObject* UGameplayCueStaticBase::GetAssetObject()
{
	if (this->CharacterDataAsset.IsNull() == true) return nullptr;
	UObject* Asset = GetGameInstance()->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());

	return Asset;
}

UCharacterDataAsset* UGameplayCueStaticBase::GetCharacterAsset()
{
	return Cast<UCharacterDataAsset>(GetAssetObject());

}


UGAS_GameInstance* UGameplayCueStaticBase::GetGameInstance()
{
	return Cast<UGAS_GameInstance>(GetCharacter()->GetGameInstance());


}

