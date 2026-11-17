

#include "ObjectPoolSystem/ObjectPoolSystem.h"
#include "GameInstance/GAS_GameInstance.h"
#include "Component/ObjectPoolSystemComponent.h"




UObjectPoolSystem::UObjectPoolSystem()
{

}

TArray<FString> UObjectPoolSystem::GetAllPoolName()
{
	TArray<FString> Array;
	this->ObjectPoolMap.GenerateKeyArray(Array);

	return Array;
}


void UObjectPoolSystem::ReturnObject(const FString& PoolName, AActor* Object)
{
	checkf(Object,TEXT("UObjectPoolSystem::ReturnObject(): Object == nullptr !!!!"));
	if (this->ObjectPoolMap.Find(PoolName) == nullptr)
	{
		TSet<AActor*> Pool;
		Pool.Add(Object);
		this->ObjectPoolMap.Add(PoolName, Pool);

	}
	else
	{
		TSet<AActor*>& Pool = *this->ObjectPoolMap.Find(PoolName);
		Pool.Add(Object);
	}
	


}

int32 UObjectPoolSystem::GetPoolSize(const FString& PoolName)
{
	if (this->ObjectPoolMap.Find(PoolName) == nullptr) return -1;
	TSet<AActor*>& Pool = *this->ObjectPoolMap.Find(PoolName);
	return Pool.Num();
}

void UObjectPoolSystem::ClearPool(const FString& PoolName)
{
	if (this->ObjectPoolMap.Find(PoolName) == nullptr) return;
	TSet<AActor*>& Pool = *this->ObjectPoolMap.Find(PoolName);
	for (auto& Element : Pool)
	{
		Element->Destroy();
	}
	Pool.Empty();

}

void UObjectPoolSystem::ClearAllPool()
{
	for (auto& Element1:this->ObjectPoolMap)
	{
		for (auto& Element2 : Element1.Value)
		{
			Element2->Destroy();
		}
		Element1.Value.Empty();
	}

}

AActor* UObjectPoolSystem::GetObject(UClass* ObjectClass, const FString& PoolName, const FTransform& ObjectTransform)
{

	AActor* Object = nullptr;
	TSet<AActor*>* Pool = this->ObjectPoolMap.Find(PoolName);
	if (Pool == nullptr || Pool->Num() == 0)
	{
		Object = GetWorld()->SpawnActor<AActor>(ObjectClass, ObjectTransform.GetLocation(), ObjectTransform.Rotator());
		if (Object != nullptr)
		{
			Object->SetActorScale3D(ObjectTransform.GetScale3D());
		}

		return Object;
	}
	for (auto& Element : *Pool)
	{
		if (Element == nullptr) continue;
		Object = Element;
		Object->SetActorTransform(ObjectTransform);
		Pool->Remove(Object);
		return Object;
	}
	return nullptr;

}


bool UObjectPoolSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (Cast<UGAS_GameInstance>(Outer)->IsDedicatedServerInstance() == true) return false;
	TArray<UClass*> SystemClassArray;
	GetDerivedClasses(GetClass(), SystemClassArray);
	return SystemClassArray.IsEmpty();

}