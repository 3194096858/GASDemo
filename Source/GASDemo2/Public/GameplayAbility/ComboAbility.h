
#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility/GameplayAbilityBase.h"
#include "ComboAbility.generated.h"


class UDataTable;
class UComboAbilityDataAsset;

UCLASS()
class GASDEMO2_API UComboAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
public:

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;



public:

protected:
	TArray<AActor*> IgnoreActorArray;
	
protected:
	/*UFUNCTION(BlueprintCallable)
	void Initialize();*/
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetMontageNumber();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UAnimMontage* GetMontage(int32 Index);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetComboInterval();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentComboNumber();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ExecuteCollisionDetection();
	void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray);
private:
	


};
