
#pragma once

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGAS_AbilitySystemComponent;
class UGAS_AttributeSet;
class UStateComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataTable;
class UWidgetComponent;
class AWeaponBase;
class UCollisionDetectionComponent;
class UCharacterDataAsset;
class UObjectPoolSystemComponent;
class UProjectileDataAsset;

UCLASS()
class GASDEMO2_API ACharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ACharacterBase();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UGAS_AbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UGAS_AttributeSet> AttributeSet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCollisionDetectionComponent> CollisionDetectionComponent;
	FString CharacterName = TEXT("Quinn");
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UCharacterDataAsset> CharacterDataAsset;
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UProjectileDataAsset> ProjectileDataAsset;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandleMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UObjectPoolSystemComponent> ObjectPoolSystemComponent;

public:
	UFUNCTION(BlueprintCallable)
	FString GetAbilityName(const FGameplayAbilitySpecHandle& SpecHandle);
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> GetAllCooldownAbilitySpecHandle();
	UFUNCTION(BlueprintCallable)
	virtual void ExecuteCollisionDetection();
	UFUNCTION(Server, Reliable)
	void Server_InitializeAbility();
	UFUNCTION(Server, Reliable)
	void Server_GiveAllAbility();
	UFUNCTION(Server, Reliable)
	void Server_InitializeAttribute();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_EnableCollision();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_DisableCollision();
	UFUNCTION(BlueprintCallable,Server,Reliable)
	void Server_ActivateAbility(const FGameplayTag& AbilityTag);
	UFUNCTION()
	void ActivateAbility(const FGameplayTag& AbilityTag);
	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GetAbilitySpecHandle(const FGameplayTag& AbilityTag);
	UFUNCTION(Client, Reliable)
	void Client_CancelAbility(const FGameplayTag& AbilityTag);
	UFUNCTION(Server, Reliable)
	void Server_CancelAbility(const FGameplayTag& AbilityTag);
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticast_SetMeshOpacity(float NewOpacity);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetMeshGlow(float NewValue);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetMeshGlowColor(const FVector& NewColor);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline FString GetCharacterName()
	{
		return CharacterName;
	};
	inline UCollisionDetectionComponent* GetCollisionDetectionComponent() const
	{
		return CollisionDetectionComponent;
	};
protected:
	UFUNCTION()
	virtual void OnAssetLoadCompletion(const FString& AssetPath);
	UFUNCTION()
	virtual void OnMontageEnd(UAnimMontage* Montage,bool bInterrupted);
	UFUNCTION()
	virtual void OnMontageStart(UAnimMontage* Montage);
	UFUNCTION()
	virtual void OnPlayerLogin(APlayerController* PlayerController);
	virtual void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray);

};
