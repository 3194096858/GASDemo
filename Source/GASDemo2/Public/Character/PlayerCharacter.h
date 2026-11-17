// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GASDEMO2_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Landed(const FHitResult& Hit) override;

public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AWeaponBase> Weapon;
	int32 PlayerID = 0;
	bool IsEquipWeapon = false;
	
public:

	UFUNCTION(Server,Reliable)
	void Server_SetWeaponOpacity(float NewOpacity);

	/*UFUNCTION(Server, Reliable)
	 void Server_InitializeAttribute();*/
	/*UFUNCTION(Server, Reliable)
	void Server_GiveAllAbility();*/

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetPlayerID(int32 NewID);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline int32 GetPlayerID()
	{
		return PlayerID;
	};
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline AWeaponBase* GetWeapon()
	{
		return Weapon;
	};
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool GetIsEquipWeapon()
	{
		return IsEquipWeapon;
	};
	UFUNCTION(BlueprintCallable)
	inline void SetIsEquipWeapon(bool NewValue)
	{
		IsEquipWeapon = NewValue;
	};
	UFUNCTION(BlueprintCallable)
	void EquipWeapon();
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();
	virtual void ExecuteCollisionDetection() override;

protected:
	virtual void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray) override;

};
