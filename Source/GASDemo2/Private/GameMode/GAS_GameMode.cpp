#include "GameMode/GAS_GameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Character/PlayerCharacter.h"

#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"
#include "Projectile/ProjectileBase.h"



void AGAS_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	FTimerHandle Timer;

	GetWorld()->GetTimerManager().SetTimer(Timer, this,&AGAS_GameMode::InitializePlayerID,1.0f,false);
	GetWorld()->GetTimerManager().ClearTimer(this->PlayerLoginTimerHandle);
	GetWorld()->GetTimerManager().SetTimer
	(
		this->PlayerLoginTimerHandle, 
		[this,NewPlayer]()
		{
			this->PlayerLoginDelegate.Broadcast(NewPlayer);
		},
		1.0f, 
		false
	);

}

void AGAS_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options,Address,UniqueId,ErrorMessage);
}

void AGAS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	///UObjectPoolSystem::Get()->GetObject<AProjectileBase>(ObjectClass, TEXT("Projectile"), ObjectTransform);



}

void AGAS_GameMode::BindPlayerLoginDelegate(UObject* Object, const FName& CallbackFunction)
{
	if (this->PlayerLoginDelegate.IsBoundToObject(Object) == true) return;

	this->PlayerLoginDelegate.AddUFunction(Object,CallbackFunction);

}

void AGAS_GameMode::UnbindPlayerLoginDelegate(UObject* Object)
{
	if (this->PlayerLoginDelegate.IsBoundToObject(Object) == false) return;

	this->PlayerLoginDelegate.RemoveAll(this);


}

void AGAS_GameMode::InitializePlayerID()
{
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		APlayerCharacter* Character = Cast<APlayerCharacter>(GameState->PlayerArray[i]->GetPawn());
		Character->NetMulticast_SetPlayerID(i + 1);

	}

}
//
//
//AActor* AGAS_GameMode::SpawnProjectile(UClass* ObjectClass,const FTransform& ObjectTransform)
//{
//	//UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
//
//	AActor* Projectile = UObjectPoolSystem::Get()->GetObject<AProjectileBase>(ObjectClass, TEXT("Projectile"), ObjectTransform);
//	GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("SpawnProjectile(): PoolSize == %d"), UObjectPoolSystem::Get()->GetPoolSize(TEXT("Projectile"))));
//
//	return Projectile;
//}