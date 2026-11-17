
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GAS_AssetManager.generated.h"

class UDataTable;
class UInputDataAsset;

DECLARE_MULTICAST_DELEGATE_OneParam(FAssetLoadCompletionDelegate, const FString&);


UCLASS(Blueprintable)
class GASDEMO2_API UGAS_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:



public:

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputDataAsset> InputDataAsset;

private:
	TMap<FStreamableHandle*, UObject*> AssetMap;
	TMap<FString, FStreamableHandle*> AssetHandleMap;
	FAssetLoadCompletionDelegate AssetLoadCompletionDelegate;

public:
	void BindAssetLoadCompletionDelegate(UObject* Object,const FString& CallbackFunction);
	void UnbindAssetLoadCompletionDelegate(UObject* Object);
	void LoadAsset(const TSoftObjectPtr<UObject>& AssetObject);
	void UnloadAsset(const FString& AssetPath);
	UObject* GetAsset(const FString& AssetPath);
	inline UInputDataAsset* GetInputDataAsset()
	{
		return InputDataAsset;
	};
protected:


	
};
