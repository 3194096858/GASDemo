
#include "GameplayCue/Actor/ShieldCue.h"



#include "Character/CharacterBase.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/CharacterDataAsset.h"
#include "AssetManager/GAS_AssetManager.h"



void AShieldCue::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget,EventType,Parameters);
	/*switch (EventType)
	{
	case EGameplayCueEvent::OnActive:
		Server_SetTimer();

		break;
	case EGameplayCueEvent::Removed:

		Server_ClearTimer();
		break;

	}*/
	//Parameters.Effec
	//GetCharacter()->GetAbilitySystemComponent()->RemoveGameplayCue(Tag::Cue::Shield);

}











