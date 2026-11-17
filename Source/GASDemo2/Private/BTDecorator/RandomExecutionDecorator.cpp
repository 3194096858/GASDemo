

#include "BTDecorator/RandomExecutionDecorator.h"




bool URandomExecutionDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp,NodeMemory);
	if (this->Probability <= 0.0f) return false;
	if (this->Probability >= 1.0f) return true;
	int32 RandomNumber = FMath::RandRange(0, 100);
	if (this->Probability * 100 > RandomNumber) return true;
	return false;
}
