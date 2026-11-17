

#include "GameplayCue/Actor/GameplayCueActorBase.h"


#include "Character/CharacterBase.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/CharacterDataAsset.h"
#include "AssetManager/GAS_AssetManager.h"


void AGameplayCueActorBase::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{

	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	this->Character = Cast<ACharacterBase>(MyTarget);


}





ACharacterBase* AGameplayCueActorBase::GetCharacter()
{
	return this->Character;
}


UObject* AGameplayCueActorBase::GetAssetObject()
{
	if (this->CharacterDataAsset.IsNull() == true) return nullptr;
	UObject* Asset = GetGameInstance()->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());

	return Asset;
}

UCharacterDataAsset* AGameplayCueActorBase::GetCharacterAsset()
{
	return Cast<UCharacterDataAsset>(GetAssetObject());

}


UGAS_GameInstance* AGameplayCueActorBase::GetGameInstance()
{
	return Cast<UGAS_GameInstance>(GetCharacter()->GetGameInstance());


}

