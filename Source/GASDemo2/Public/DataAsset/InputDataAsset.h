
#pragma once

#include "GameplayTag/GameplayTag.h"


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

struct FGameplayTag;
class UInputAction;
class UInputMappingContext;

UCLASS()
class GASDEMO2_API UInputDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContextArray;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TMap<FGameplayTag, UInputAction*> InputMap;

public:
	UInputAction* GetInputAction(const FGameplayTag& Tag);

	
};
