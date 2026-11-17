
#pragma once

#include "DataAsset/InputDataAsset.h"



#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAS_PlayerController.generated.h"

struct FInputActionValue;
class UCharacterDataAsset;
class UProjectileDataAsset;




UCLASS()
class GASDEMO2_API AGAS_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

public:
	FVector2D MovementInputValue;
protected:
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UCharacterDataAsset> CharacterDataAsset;
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UProjectileDataAsset> ProjectileDataAsset;

	FTimerHandle PlayerRespawnTimerHandle;
	FTimerHandle CharacterMeshOpacityTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerRespawnTimeleft = 30;

public:
	UFUNCTION(Server, Reliable)
	void Server_UpdateCharacterMeshOpacity();
	UFUNCTION(Server, Reliable)
	void Server_InitializeCharacterAttribute();
	UFUNCTION()
	void OnLook(const FInputActionValue& Value);
	UFUNCTION()
	void OnJumpAbilityActivated();
	UFUNCTION()
	void OnMovementAbilityActivated(const FInputActionValue& Value);
	UFUNCTION()
	void OnDashAbilityActivated();
	UFUNCTION()
	void OnProjectileAbilityActivated();
	UFUNCTION()
	void OnShieldAbilityActivated();
	UFUNCTION()
	void OnComboAbilityActivated();

	UFUNCTION(Server,Reliable)
	void Server_InitializeCharacterAbility();
	UFUNCTION()
	void OnCharacterAssetLoadCompletion(const FString& AssetPath);

	UFUNCTION(Server,Reliable)
	void Server_OnPlayerDied();

	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerHealthBar();

	UFUNCTION(Server, Reliable)
	void Server_OnPlayerRespawn();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetPlayerRespawnTimeleft()
	{
		return PlayerRespawnTimeleft;
	};
protected:
	UFUNCTION()
	void UpdateCharacterMeshOpacity();
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerRespawnCountdown();
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerDied();

	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerRespawn();

	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerHealthBar();
	UFUNCTION(BlueprintNativeEvent)
	void OnCharacterAbilityInitializeCompletion();

};
