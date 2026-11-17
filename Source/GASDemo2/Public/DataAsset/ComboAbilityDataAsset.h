
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/AbilityDataAsset.h"
#include "ComboAbilityDataAsset.generated.h"



class UGameplayAbilityBase;
class UGameplayAbility;
class UAnimMonatge;
class UGameplayEffect;
class ACharacterBase;
class AProjectileBase;

UCLASS()
class GASDEMO2_API UComboAbilityDataAsset : public UAbilityDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UAnimMontage*> MontageArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UParticleSystem*> VFXArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Interval = 1.0f;

	
};
