#pragma once

#include "CoreMinimal.h"
#include "GameplayCue/Actor/GameplayCueActorBase.h"
#include "ShieldCue.generated.h"




UCLASS()
class GASDEMO2_API AShieldCue : public AGameplayCueActorBase
{
	GENERATED_BODY()
	

protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;



public:



protected:
	UPROPERTY(BlueprintReadOnly)
	float Defense = 0.0f;


private:


public:



protected:
	
private:

};
