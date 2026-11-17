

#include "GameplayCue/Static/DashCue.h"



#include "Character/CharacterBase.h"
#include "Struct/GAS_GameplayEffectContext.h"
#include "Kismet/GameplayStatics.h"

#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"

#include "DataAsset/CharacterDataAsset.h"
#include "DataAsset/DashAbilityDataAsset.h"
#include "GameplayTag/GameplayTag.h"

void UDashCue::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	UDashAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UDashAbilityDataAsset>(Tag::Ability::Dash);
	///this->Distance = Asset->Distance;

	switch (EventType)
	{
	case EGameplayCueEvent::OnActive:
		GetCharacter()->GetMesh()->SetVisibility(false);

		if (Asset == nullptr) return;

		UGameplayStatics::SpawnEmitterAttached(Asset->DashVFX, GetCharacter()->GetMesh());


		break;
	case EGameplayCueEvent::Removed:
		GetCharacter()->GetMesh()->SetVisibility(true);

		break;

	}
	


}


