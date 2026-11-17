
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "ShieldAbility.generated.h"






UCLASS()
class GASDEMO2_API UShieldAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()


public:
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
public:



public:



protected:
	UPROPERTY(BlueprintReadOnly)
	float DefenseIncrease = 5.0f;


private:
	FTimerHandle TimerHandle;

public:



protected:
	UFUNCTION(Server, Reliable)
	void Server_SetTimer();
	
private:



	
};
