

#include "BTTask/FaceToTargetTask.h"
#include "BehaviorTree/BlackboardComponent.h"

//#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controller/AIController/GAS_AIController.h"


EBTNodeResult::Type UFaceToTargetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);
	APawn* NPC = OwnerComp.GetAIOwner()->GetPawn();
	const FName KeyName = TEXT("TargetActor");
	const float MinRotationYaw = 10.0f;

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(KeyName));
	checkf(TargetActor, TEXT("UFaceToTargetTask::ExecuteTask():  TargetActor == nullptr !!!!"));
	
	FRotator DeltaRotation = UKismetMathLibrary::FindLookAtRotation(NPC->GetActorLocation(),TargetActor->GetActorLocation());
	if (FMath::Abs(DeltaRotation.Yaw) > MinRotationYaw)
	{
		NPC->SetActorRotation(FRotator(NPC->GetActorRotation().Pitch, DeltaRotation.Yaw, NPC->GetActorRotation().Roll));
	}

	///OwnerComp.log

	return EBTNodeResult::Succeeded;
}