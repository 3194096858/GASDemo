

#include "Controller/AIController/GAS_AIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "AttributeSet/GAS_AttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/WeaponBase.h"
#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/NPCDataAsset.h"


AGAS_AIController::AGAS_AIController()
{
	this->AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	this->AIPerceptionComponent->SetIsReplicated(true);

}

void AGAS_AIController::BeginPlay()
{
	Super::BeginPlay();

}

void AGAS_AIController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AGAS_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGAS_AIController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	GetBlackboardComponent();
	///GetComponent
	///GetBehaviorTree
	///RunBehaviorTree();
	//UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);

}

void AGAS_AIController::Server_RunBehaviorTree_Implementation()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(this->BrainComponent);

	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* AssetObject = GameInstance->GetAssetManager()->GetAsset(this->NPCDataAsset.ToString());
	checkf(AssetObject, TEXT("AGAS_AIController::Server_RunBehaviorTree(): AssetObject == nullptr !!!!"));
	UNPCDataAsset* Asset = Cast<UNPCDataAsset>(AssetObject);
	if (BTComponent == nullptr)
	{
		RunBehaviorTree(Asset->BehaviorTree);
	}
}

void AGAS_AIController::Server_ResumeBehaviorTree_Implementation()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(this->BrainComponent);

	BTComponent->ResumeLogic(TEXT("Resume"));

}

void AGAS_AIController::Server_PauseBehaviorTree_Implementation()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(this->BrainComponent);

	BTComponent->PauseLogic(TEXT("Pause"));


}
//
//void AGAS_AIController::PauseBehaviorTree()
//{
//	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(this->BrainComponent);
//
//	BTComponent->PauseLogic(TEXT("Pause"));
//
//
//}
//
//void AGAS_AIController::ResumeBehaviorTree()
//{
//	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(this->BrainComponent);
//
//	BTComponent->ResumeLogic(TEXT("Resume"));
//
//
//}
