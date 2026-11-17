
#pragma once


#include "AbilityDataAsset.h"
#include "GameplayTag/GameplayTag.h"
///#include "AbilitySystemComponent.h"


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"


class UGameplayAbilityBase;
class UGameplayAbility;
class UAnimMonatge;
class UGameplayEffect;
class ACharacterBase;
class AProjectileBase;
class UAbilityDataAsset;


UCLASS()
class GASDEMO2_API UCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ACharacterBase> CharacterClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> AbilityClassMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UAnimMontage*> HitReactionMontageMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> EffectClassMap;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, UAbilityDataAsset*> AbilityAssetMap;


public:
	template<class T>
	T* GetAbilityAsset(const FGameplayTag& AbilityTag)
	{
		UAbilityDataAsset** Asset = AbilityAssetMap.Find(AbilityTag);
		checkf(Asset, TEXT("UCharacterDataAsset::GetAbilityAsset(): Asset == nullptr !!!!"));

		return Cast<T>(*Asset);
	};



	
};









