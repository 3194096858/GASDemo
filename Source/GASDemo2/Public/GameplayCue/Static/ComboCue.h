
#pragma once

#include "CoreMinimal.h"
#include "GameplayCue/Static/GameplayCueStaticBase.h"
#include "ComboCue.generated.h"



UCLASS()
class GASDEMO2_API UComboCue : public UGameplayCueStaticBase
{
	GENERATED_BODY()
protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;


	
};
