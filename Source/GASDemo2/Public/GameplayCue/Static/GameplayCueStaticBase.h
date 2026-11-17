
#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueStaticBase.generated.h"


class ACharacterBase;
class UGAS_GameInstance;
class UCharacterDataAsset;
class UAbilityDataAsset;


UCLASS()
class GASDEMO2_API UGameplayCueStaticBase : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;


protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ACharacterBase> Character;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UCharacterDataAsset> CharacterDataAsset;

	
protected:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	ACharacterBase* GetCharacter();
	UGAS_GameInstance* GetGameInstance();
	UFUNCTION()
	UObject* GetAssetObject();
	UFUNCTION()
	UCharacterDataAsset* GetCharacterAsset();






	
};
