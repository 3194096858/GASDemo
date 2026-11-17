
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindRandomLocationTask.generated.h"

UCLASS()
class GASDEMO2_API UFindRandomLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName KeyName = TEXT("CurrentRandomLocation");


};
