
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GAS_GameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLoginDelegate,APlayerController*);


UCLASS()
class GASDEMO2_API AGAS_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
protected:
	virtual void BeginPlay() override;

public:

protected:
	FPlayerLoginDelegate PlayerLoginDelegate;
	FTimerHandle PlayerLoginTimerHandle;

public:
	void BindPlayerLoginDelegate(UObject* Object, const FName& CallbackFunction);
	void UnbindPlayerLoginDelegate(UObject* Object);

protected:
	void InitializePlayerID();
	





	
};
