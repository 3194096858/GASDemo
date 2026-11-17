

#include "Grave/Grave.h"
#include "Component/ObjectPoolSystemComponent.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"

#include "Components/CapsuleComponent.h"
#include "Character/PlayerCharacter.h"
#include "DataAsset/CharacterDataAsset.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "Projectile/ProjectileBase.h"
#include "Controller/PlayerController/GAS_PlayerController.h"
#include "GameMode/GAS_GameMode.h"
#include "GameplayTag/GameplayTag.h"
#include "GameplayEffect.h"
#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/NPC.h"
#include "DataAsset/NPCDataAsset.h"


AGrave::AGrave()
{
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	this->ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	SetRootComponent(this->CapsuleComponent);

	this->PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	this->ParticleSystemComponent->SetupAttachment(this->CapsuleComponent);

	this->ParticleSystemComponent->SetRelativeLocation(FVector(-60.0f,0.0f,-40.0f));
	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AGrave::BeginPlay()
{
	Super::BeginPlay();
	Cast<UGAS_GameInstance>(GetGameInstance())->GetAssetManager()->LoadAsset(this->NPCDataAsset);

	GetWorld()->GetTimerManager().SetTimer(this->ZombieSpawnTimerHandle,this,&AGrave::SpawnZombie,20.0f,true,2.0f);
	//GetWorld()->GetTimerManager().SetTimer(this->ZombieSpawnTimerHandle, this, &AGrave::SpawnZombie, 3.0f, false, 2.0f);

}

void AGrave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrave::Server_SpawnZombie_Implementation()
{
	FTransform SpawnTransform = GetActorTransform();
	static FString PoolName = TEXT("Zombie");
	AActor* Actor = nullptr;
	///static bool i = true;
	const FVector LocationOffset = FVector(FMath::RandRange(-200.0f,200.0f), FMath::RandRange(-200.0f, 200.0f),0.0f);
	SpawnTransform.SetLocation(GetActorLocation()+LocationOffset);
	UObject* AssetObject = Cast<UGAS_GameInstance>(GetGameInstance())->GetAssetManager()->GetAsset(this->NPCDataAsset.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("  ZombiePoolSize == %d !!!!!!"), UObjectPoolSystem::Get(GetGameInstance())->GetPoolSize(TEXT("Zombie"))));

	checkf(AssetObject, TEXT("AGrave::Server_SpawnZombie(): AssetObejct == nullptr !!!"));
	UNPCDataAsset* Asset = Cast<UNPCDataAsset>(AssetObject);
	
	Actor = UObjectPoolSystem::Get(GetGameInstance())->GetObject(Asset->CharacterClass, PoolName, SpawnTransform);
	ANPC* NPC = Cast<ANPC>(Actor);
	NPC->GetObjectPoolSystemComponent()->ActivatedOwner();
	OnZombieSpawn();

	
	


}

void AGrave::OnZombieSpawn_Implementation()
{



}

void AGrave::SpawnZombie()
{
	Server_SpawnZombie();


}

