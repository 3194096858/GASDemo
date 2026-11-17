#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"





UCLASS()
class GASDEMO2_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()



protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<FString> StateArray;





	
};










