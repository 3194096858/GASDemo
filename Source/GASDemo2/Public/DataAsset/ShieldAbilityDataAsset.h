
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/AbilityDataAsset.h"
#include "ShieldAbilityDataAsset.generated.h"




UCLASS()
class GASDEMO2_API UShieldAbilityDataAsset : public UAbilityDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefenseIncrease = 5.0f;


};
