
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GAS_AIController.generated.h"


class UAIPerceptionComponent;
class UNPCDataAsset;


UCLASS()
class GASDEMO2_API AGAS_AIController : public AAIController
{
	GENERATED_BODY()
public:
	AGAS_AIController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* aPawn) override;
public:

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UNPCDataAsset> NPCDataAsset;
public:
	UFUNCTION(Server,Reliable)
	void Server_PauseBehaviorTree();
	UFUNCTION(Server, Reliable)
	void Server_ResumeBehaviorTree();
	UFUNCTION(Server, Reliable)
	void Server_RunBehaviorTree();

protected:
	


};
