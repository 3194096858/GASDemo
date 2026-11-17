
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "HitReactionAbility.generated.h"

struct FGameplayTag;


UCLASS()
class GASDEMO2_API UHitReactionAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMontageNumber();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAnimMontage* GetMontage(const FGameplayTag& AttackDirectionTag);




};
