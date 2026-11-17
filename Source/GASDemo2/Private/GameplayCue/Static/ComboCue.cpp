#include "GameplayCue/Static/ComboCue.h"


#include "Character/CharacterBase.h"
#include "Struct/GAS_GameplayEffectContext.h"
#include "Kismet/GameplayStatics.h"

#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"

#include "DataAsset/CharacterDataAsset.h"
#include "DataAsset/ComboAbilityDataAsset.h"

void UComboCue::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	if (EventType !=EGameplayCueEvent::Executed) return;
	UComboAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UComboAbilityDataAsset>(Tag::Ability::Combo);
	if (Asset == nullptr) return;

	const FGAS_GameplayEffectContext* EffectContext = static_cast<const FGAS_GameplayEffectContext*>(Parameters.EffectContext.Get());
	int32 CurrentComboNumber = EffectContext->ComboEffectData.CurrentComboNumber;
	FVector SpawnLocation = EffectContext->GetHitResult()->ImpactPoint;

	if (Asset->VFXArray.IsValidIndex(CurrentComboNumber - 1) == false) return;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Asset->VFXArray[CurrentComboNumber - 1],SpawnLocation);

}


