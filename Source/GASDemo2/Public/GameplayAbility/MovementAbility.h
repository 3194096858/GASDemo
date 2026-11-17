
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "MovementAbility.generated.h"





UCLASS()
class GASDEMO2_API UMovementAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
