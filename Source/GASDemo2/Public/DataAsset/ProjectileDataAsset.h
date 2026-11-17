
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileDataAsset.generated.h"




class UGameplayAbilityBase;
class UGameplayAbility;
class UAnimMonatge;
class UGameplayEffect;
class ACharacterBase;
class AProjectileBase;




UCLASS()
class GASDEMO2_API UProjectileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Lifetime = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* VFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* HitVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;


};
