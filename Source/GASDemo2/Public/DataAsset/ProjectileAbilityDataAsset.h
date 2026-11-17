
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/AbilityDataAsset.h"
#include "ProjectileAbilityDataAsset.generated.h"


class UProjectileDataAsset;


UCLASS()
class GASDEMO2_API UProjectileAbilityDataAsset : public UAbilityDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> Montage;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileDataAsset> ProjectileAsset;*/



	
};
