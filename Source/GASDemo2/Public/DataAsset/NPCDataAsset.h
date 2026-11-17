
#pragma once

#include "CoreMinimal.h"
#include "DataAsset/CharacterDataAsset.h"
#include "NPCDataAsset.generated.h"

class UBehaviorTree;

UCLASS()
class GASDEMO2_API UNPCDataAsset : public UCharacterDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* RespawnMontage;






	
};
