
#pragma once

//#include "GameFramework/GameInstance.h"
//#include "Component/ObjectPoolSystemComponent.h"
#include "GameInstance/GAS_GameInstance.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectPoolSystem.generated.h"

class UGameInstance;
class UObjectPoolSystemComponent;
class UGAS_GameInstance;

UCLASS()
class GASDEMO2_API UObjectPoolSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UObjectPoolSystem();
protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	TMap<FString, TSet<AActor*>> ObjectPoolMap;
public:
	TArray<FString> GetAllPoolName();
	void ReturnObject(const FString& PoolName, AActor* Object);
	int32 GetPoolSize(const FString& PoolName);
	void ClearPool(const FString& PoolName);
	void ClearAllPool();
	AActor* GetObject(UClass* ObjectClass, const FString& PoolName, const FTransform& ObjectTransform);
	static inline UObjectPoolSystem* Get(UGameInstance* GameInstance)
	{
		return UGameInstance::GetSubsystem<UObjectPoolSystem>(GameInstance);
	};
	
};
