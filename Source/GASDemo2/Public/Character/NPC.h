
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "NPC.generated.h"

UCLASS()
class GASDEMO2_API ANPC : public ACharacterBase
{
	GENERATED_BODY()

public:
	ANPC();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:


public:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_OnActivated();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_OnDeactivated();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_PlayRespawnMontage(float PlayRate = 1.0f);
	UFUNCTION()
	inline UObjectPoolSystemComponent* GetObjectPoolSystemComponent()
	{
		return ObjectPoolSystemComponent;
	};
	UFUNCTION(Server,Reliable)
	void Server_OnDied();
	UFUNCTION(Server, Reliable)
	void Server_UpdateHealthBar();
	UFUNCTION(BlueprintCallable,Server,Reliable)
	void Server_Respawn();
	UFUNCTION(BlueprintCallable)
	void Deactivated();
	
	virtual void ExecuteCollisionDetection() override;

protected:
	UFUNCTION(Server,Reliable)
	void Server_RunBehaviorTree();
	virtual void OnAssetLoadCompletion(const FString& AssetPath) override;
	UFUNCTION(BlueprintNativeEvent)
	void UpdateHealthBar();
	UFUNCTION(BlueprintNativeEvent)
	void OnDied();
	UFUNCTION(BlueprintNativeEvent)
	void OnRespawn();
	UFUNCTION()
	void OnActivated();
	UFUNCTION()
	void OnDeactivated();
	virtual void OnMontageStart(UAnimMontage* Montage) override;
	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void OnPlayerLogin(APlayerController* PlayerController) override;
	virtual void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray) override;

};
