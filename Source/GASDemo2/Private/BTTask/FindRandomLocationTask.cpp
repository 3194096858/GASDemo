// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask/FindRandomLocationTask.h"


#include "NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controller/AIController/GAS_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFindRandomLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* NPC = OwnerComp.GetAIOwner()->GetPawn();
	FNavLocation RandomLocation;
	UNavigationSystemV1* System = UNavigationSystemV1::GetNavigationSystem(NPC);
	System->GetRandomReachablePointInRadius(NPC->GetActorLocation(), this->Radius, RandomLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(this->KeyName,RandomLocation.Location);

	return EBTNodeResult::Succeeded;
}