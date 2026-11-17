
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GAS_GameInstance.generated.h"


class UGAS_AssetManager;


UCLASS()
class GASDEMO2_API UGAS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
protected:
	virtual void Init() override;
	virtual void OnStart() override;


public:

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGAS_AssetManager> AssetManagerClass;
	
	UPROPERTY()
	TObjectPtr<UGAS_AssetManager> AssetManager;
public:

	inline UGAS_AssetManager* GetAssetManager() const
	{
		return AssetManager;
	};

protected:


};
