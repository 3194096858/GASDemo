
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolSystemComponent.generated.h"

DECLARE_DELEGATE(FActivationDeLegate);
DECLARE_DELEGATE(FDeactivationDeLegate);
DECLARE_DELEGATE(FLifetimeLoopingDeLegate);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASDEMO2_API UObjectPoolSystemComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UObjectPoolSystemComponent();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	FActivationDeLegate ActivationDeLegate;
	FDeactivationDeLegate DeactivationDeLegate;
	FLifetimeLoopingDeLegate LifetimeLoopingDeLegate;
protected:
	float Lifetime = 0.0f;
	bool IsActivated = false;
	FTimerHandle LifetimeTimerHandle;
	FTimerHandle LifetimeLoopingTimerHandle;
	float LoopingFrequency = 0.1f;
public:
	void ActivatedOwner();
	void DeactivatedOwner();
	void OnLoop();
	void ReturnObjectToSystem(const FString& PoolName, AActor* Object);
	AActor* GetActorFromSystem(UClass* ObjectClass, const FString& PoolName, const FTransform& ObjectTransform);
	template<class T>
	T* GetObjectFromSystem(UClass* ObjectClass, const FString& PoolName, const FTransform& ObjectTransform)
	{
		return Cast<T>(GetActorFromSystem(ObjectClass,PoolName,ObjectTransform));

	};
	inline bool GetIsActivated() const
	{
		return IsActivated;

	};
	inline void SetIsActivated(bool NewValue)
	{
		IsActivated = NewValue;
	};
	inline float GetLifetime() const
	{
		return Lifetime;

	};
	void SetLifetime(float NewValue)
	{
		Lifetime = NewValue;
	};
	inline float GetLoopingFrequency() const
	{
		return LoopingFrequency;

	};
	inline void SetLoopingFrequency(float NewValue)
	{
		LoopingFrequency = NewValue;
	};
		
};
