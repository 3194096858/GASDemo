
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"



class UGAS_AbilitySystemComponent;
class UGAS_AttributeSet;
class UStateComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataTable;
class UWidgetComponent;
class UCapsuleComponent;
class UCollisionDetectionComponent;


UCLASS()
class GASDEMO2_API AWeaponBase : public AActor
{
	GENERATED_BODY()
public:	
	AWeaponBase();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
public:

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCollisionDetectionComponent> CollisionDetectionComponent;

public:
	


public:
	UFUNCTION(NetMulticast,Reliable)
	void NetMulticast_SetMeshOpacity(float NewOpacity);
	UFUNCTION(BlueprintCallable)
	void SetMeshGlow(float NewValue);
	UFUNCTION(BlueprintCallable)
	void SetMeshGlowColor(const FVector& NewColor);
	UFUNCTION(BlueprintCallable)
	void SetMeshOpacity(float NewOpacity);
	UFUNCTION(BlueprintCallable)
	FVector GetCenterLocation();
	UFUNCTION(BlueprintCallable)
	float GetWeaponRadius();
	UFUNCTION(BlueprintCallable)
	float GetWeaponLength();
	UFUNCTION(BlueprintCallable)
	void SetMeshLocation(const FVector& NewLocation);
	UFUNCTION(BlueprintCallable)
	void ExecuteCollisionDetection();
	FVector GetMeshSlotLocation(const FString& SlotName);

protected:
	///UFUNCTION(BlueprintNativeEvent)
	void OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray);









};
