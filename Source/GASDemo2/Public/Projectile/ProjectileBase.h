
#pragma once
#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"




class UGAS_AbilitySystemComponent;
class UGAS_AttributeSet;
class UStateComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataTable;
class UWidgetComponent;
class UCapsuleComponent;
class UCollisionDetectionComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class UProjectileDataAsset;
class UObjectPoolSystemComponent;

UCLASS()
class GASDEMO2_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCollisionDetectionComponent> CollisionDetectionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UObjectPoolSystemComponent> ObjectPoolSystemComponent;
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UProjectileDataAsset> ProjectileDataAsset;

private:
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
public:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_SetLifetime(float NewValue);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_OnActivated();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_OnDeactivated();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ExecuteCollisionDetection();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SetDamageEffectSpecHandle(const FGameplayEffectSpecHandle& NewEffectSpecHandle);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_SpawnHitVFX(const FString& AssetPath,const FVector& Location);
	UFUNCTION(BlueprintCallable)
	void SetVelocity(float Speed,const FVector& Direction);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void NetMulticast_ReturnObjectPool();
	UFUNCTION()
	inline UObjectPoolSystemComponent* GetObjectPoolSystemComponent()
	{
		return this->ObjectPoolSystemComponent;
	};
protected:
	UFUNCTION()
	void OnActivated();
	UFUNCTION()
	void OnDeactivated();
	UFUNCTION()
	void OnLoop();

	void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray);
private:



};
