
#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCueActorBase.generated.h"

class UGAS_GameInstance;



UCLASS()
class GASDEMO2_API AGameplayCueActorBase : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacterBase> Character;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UCharacterDataAsset> CharacterDataAsset;
	
public:
	

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACharacterBase* GetCharacter();
	UGAS_GameInstance* GetGameInstance();
	UFUNCTION()
	UObject* GetAssetObject();
	UFUNCTION()
	UCharacterDataAsset* GetCharacterAsset();


};
