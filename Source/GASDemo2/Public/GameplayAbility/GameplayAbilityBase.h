
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"


class ACharacterBase;
class AGAS_PlayerController;
class UGAS_GameInstance;
class UCharacterDataAsset;
class UAbilityDataAsset;


UCLASS()
class GASDEMO2_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbilityBase();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UCharacterDataAsset> CharacterDataAsset;
	//UPROPERTY(EditAnywhere)
	//TSoftObjectPtr<UAbilityDataAsset> AbilityDataAsset;

	
protected:
	UFUNCTION(BlueprintCallable)
	ACharacterBase* GetCharacter();
	UFUNCTION(BlueprintCallable)
	AGAS_PlayerController* GetPlayerController();
	UGAS_GameInstance* GetGameInstance();

	UFUNCTION()
	UCharacterDataAsset* GetCharacterAsset();
	/*template<class T>
	T* GetAbilityAsset()
	{
		checkf(AbilityDataAsset, TEXT("UGameplayAbilityBase::GetAbilityAsset(): AbilityDataAsset == nullptr"));
		UObject* Asset = GetGameInstance()->GetAssetManager()->GetAsset(AbilityDataAsset.ToString());

		return Cast<T>(Asset);
	};*/

private:
	UFUNCTION()
	UObject* GetAssetObject();


};
