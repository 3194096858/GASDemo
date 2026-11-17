
#pragma once

#include "CoreMinimal.h"
#include "GameplayCue/Static/GameplayCueStaticBase.h"
#include "DashCue.generated.h"

UCLASS()
class GASDEMO2_API UDashCue : public UGameplayCueStaticBase
{
	GENERATED_BODY()
protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;


protected:
	/*UPROPERTY(BlueprintReadOnly)
	float Distance = 0.0f;*/


};
