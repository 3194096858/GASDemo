
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "JumpAbility.generated.h"



UCLASS()
class GASDEMO2_API UJumpAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


};
