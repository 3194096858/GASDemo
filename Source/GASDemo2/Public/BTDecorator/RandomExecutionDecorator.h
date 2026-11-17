#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RandomExecutionDecorator.generated.h"





UCLASS()
class GASDEMO2_API URandomExecutionDecorator : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Probability = 0.5f;





};
