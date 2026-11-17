

#include "AssetManager/GAS_AssetManager.h"

void UGAS_AssetManager::BindAssetLoadCompletionDelegate(UObject* Object, const FString& CallbackFunction)
{
    if (this->AssetLoadCompletionDelegate.IsBoundToObject(Object) == true) return;
	this->AssetLoadCompletionDelegate.AddUFunction(Object,FName(CallbackFunction));


}


void UGAS_AssetManager::UnbindAssetLoadCompletionDelegate(UObject* Object)
{
	if (this->AssetLoadCompletionDelegate.IsBoundToObject(Object) == false) return;

	this->AssetLoadCompletionDelegate.RemoveAll(Object);

}


void UGAS_AssetManager::LoadAsset(const TSoftObjectPtr<UObject>& AssetObject)
{
	if (AssetObject.IsNull() == true) return;
	const FString Path = AssetObject.ToString();
	if (GetAsset(Path) != nullptr)
	{
		this->AssetLoadCompletionDelegate.Broadcast(Path);
		return;
	}
	FStreamableHandle* Handle = nullptr;
	Handle = this->StreamableManager.RequestAsyncLoad
	(
		Path,
		[this,Path,AssetObject]()
		{
			FStreamableHandle** LoadedHandle = this->AssetHandleMap.Find(Path);
			if (LoadedHandle == nullptr) return;
			this->AssetMap.Add(*LoadedHandle, AssetObject.Get());
			this->AssetLoadCompletionDelegate.Broadcast(Path);
		},
		0,
		true
	).Get();
	this->AssetHandleMap.Add(Path, Handle);

}

void UGAS_AssetManager::UnloadAsset(const FString& AssetPath)
{
	FStreamableHandle** Handle = this->AssetHandleMap.Find(AssetPath);
	UObject** Asset = nullptr;
	if (Handle == nullptr) return;
	Asset = this->AssetMap.Find(*Handle);
	if (Asset != nullptr)
	{
		Asset = nullptr;
	}
	(*Handle)->ReleaseHandle();

}

UObject* UGAS_AssetManager::GetAsset(const FString& AssetPath)
{
	FStreamableHandle** Handle = this->AssetHandleMap.Find(AssetPath);
	UObject** Asset = nullptr;
	if (Handle == nullptr) return nullptr;
	Asset = this->AssetMap.Find(*Handle);
	if (Asset == nullptr)
	{
		return nullptr;
	}
	return *Asset;
}

