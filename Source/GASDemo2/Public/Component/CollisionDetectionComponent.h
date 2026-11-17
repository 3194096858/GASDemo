
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionDetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASDEMO2_API UCollisionDetectionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCollisionDetectionComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDebug = false;


private:
	TArray<FHitResult> HitResultArray;
	TArray<AActor*> IgnoredActorArray;
public:
	UFUNCTION()
	TArray<FHitResult> GetAllHitResult();
	UFUNCTION()
	FHitResult GetFirstHitResult();
	UFUNCTION()
	int32 GetHitResultNumber();
	UFUNCTION()
	void LineTrace(const FVector& StartLocation, const FVector& EndLocation, const FString& ProfileName, bool IsIgnoreSelf = true);
	UFUNCTION()
	void SphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, const FString& ProfileName, bool IsIgnoreSelf = true);
	UFUNCTION()
	void BoxTrace(const FVector& StartLocation, const FVector& EndLocation, const FVector& HalfSize, const FRotator& Orientation, const FString& ProfileName, bool IsIgnoreSelf = true);
	UFUNCTION()
	void CapsuleTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius, float HalfHeight, const FString& ProfileName, bool IsIgnoreSelf = true);
	UFUNCTION()
	void RemoveAllIgnoredActor();
	UFUNCTION()
	void AddIgnoredActor(AActor* Actor);
	UFUNCTION()
	void RemoveIgnoredActor(AActor* Actor);
	UFUNCTION()
	TArray<AActor*> GetAllIgnoredActor();

private:
	UFUNCTION()
	void RemoveAllHitResult();




};
