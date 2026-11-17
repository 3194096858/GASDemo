
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grave.generated.h"


class UObjectPoolSystemComponent;
class UNPCDataAsset;
class UCapsuleComponent;

class UParticleSystemComponent;



UCLASS()
class GASDEMO2_API AGrave : public AActor
{
	GENERATED_BODY()
public:	
	AGrave();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

public:

protected:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UObjectPoolSystemComponent> ObjectPoolSystemComponent;*/
	UPROPERTY(EditAnywhere, Category = "Asset")
	TSoftObjectPtr<UNPCDataAsset> NPCDataAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	FTimerHandle ZombieSpawnTimerHandle;


public:

protected:

	UFUNCTION(Server,Reliable)
	void Server_SpawnZombie();
	UFUNCTION(BlueprintNativeEvent)
	void OnZombieSpawn();
	/*UFUNCTION()
	void OnZombieSpawnEnd();*/
private:
	UFUNCTION()
	void SpawnZombie();

};
