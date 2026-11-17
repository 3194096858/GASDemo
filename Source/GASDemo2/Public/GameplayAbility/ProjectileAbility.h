
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "ProjectileAbility.generated.h"

class UProjectileDataAsset;

UCLASS()
class GASDEMO2_API UProjectileAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
public:

protected:
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UProjectileDataAsset> ProjectileDataAsset;


protected:

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void Server_SpawnProjectile(const FTransform& ObjectTransform);

public:


protected:



};
