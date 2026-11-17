
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/AbilityDataAsset.h"
#include "DashAbilityDataAsset.generated.h"





UCLASS()
class GASDEMO2_API UDashAbilityDataAsset : public UAbilityDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* DashVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Distance = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedIncrease = 5.0f;

	
};
