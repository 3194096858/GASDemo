#include "Projectile/ProjectileBase.h"


#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"

#include "Component/CollisionDetectionComponent.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CharacterBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DataAsset/ProjectileDataAsset.h"
#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "Component/ObjectPoolSystemComponent.h"



AProjectileBase::AProjectileBase()
{
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));
	this->ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	this->ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	this->ObjectPoolSystemComponent = CreateDefaultSubobject<UObjectPoolSystemComponent>(TEXT("ObjectPoolSystemComponent"));

	this->PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(this->CapsuleComponent);
	SetReplicates(true);

	this->ParticleSystemComponent->SetupAttachment(GetRootComponent());

	this->ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	this->ProjectileMovementComponent->bAutoActivate = false;
	this->ProjectileMovementComponent->SetIsReplicated(true);

}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	this->ObjectPoolSystemComponent->ActivationDeLegate.BindUObject(this, &AProjectileBase::OnActivated);
	this->ObjectPoolSystemComponent->DeactivationDeLegate.BindUObject(this, &AProjectileBase::OnDeactivated);
	this->ObjectPoolSystemComponent->LifetimeLoopingDeLegate.BindUObject(this, &AProjectileBase::OnLoop);
	this->ObjectPoolSystemComponent->SetLoopingFrequency(0.05f);
	///this->ObjectPoolSystemComponent->SetLifetime();
}

void AProjectileBase::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	

}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);





}

void AProjectileBase::OnActivated()
{	
	NetMulticast_OnActivated();


}

void AProjectileBase::OnDeactivated()
{
	NetMulticast_OnDeactivated();

}


void AProjectileBase::OnLoop()
{

	Server_ExecuteCollisionDetection();

}


void AProjectileBase::Server_ExecuteCollisionDetection_Implementation()
{
	const FString ProfileName = TEXT("Projectile");
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation;
	this->CollisionDetectionComponent->SphereTrace(StartLocation,EndLocation,50.0f,ProfileName);

	OnCollisionDetectionEnd(this->CollisionDetectionComponent->GetAllHitResult());

}

void AProjectileBase::Server_SetDamageEffectSpecHandle_Implementation(const FGameplayEffectSpecHandle& NewEffectSpecHandle)
{
	this->DamageEffectSpecHandle = NewEffectSpecHandle;

	
}


void AProjectileBase::NetMulticast_SpawnHitVFX_Implementation(const FString& AssetPath,const FVector& Location)
{
	UObject* AssetObject = Cast<UGAS_GameInstance>(GetGameInstance())->GetAssetManager()->GetAsset(AssetPath);
	UProjectileDataAsset* Asset = Cast<UProjectileDataAsset>(AssetObject);
	checkf(Asset,TEXT("AProjectileBase::NetMulticast_SpawnHitVFX(): Asset == nullptr !!!"));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Asset->HitVFX, Location,FRotator());

}

void AProjectileBase::NetMulticast_OnActivated_Implementation()
{
	this->ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
	this->ProjectileMovementComponent->SetActive(true,true);
	this->ParticleSystemComponent->SetVisibility(true);
	checkf(this->ProjectileDataAsset, TEXT("AProjectileBase::NetMulticast_OnActivated(): this->ProjectileDataAsset == nullptr"));
	UObject* AssetObject = Cast<UGAS_GameInstance>(GetGameInstance())->GetAssetManager()->GetAsset(this->ProjectileDataAsset.ToString());
	UProjectileDataAsset* Asset = Cast<UProjectileDataAsset>(AssetObject);
	checkf(Asset,TEXT("AProjectileBase::NetMulticast_OnActivated(): Asset == nullptr"));
	this->ParticleSystemComponent->SetTemplate(Asset->VFX);
	this->CollisionDetectionComponent->AddIgnoredActor(GetInstigator());


}

void AProjectileBase::NetMulticast_OnDeactivated_Implementation()
{
	this->ProjectileMovementComponent->Velocity = FVector(0.0f);
	this->ProjectileMovementComponent->SetActive(false,true);
	SetActorLocation(FVector(0.0f,0.0f,1000.0f));
	this->CollisionDetectionComponent->RemoveAllIgnoredActor();
	this->ParticleSystemComponent->SetVisibility(false);
	////GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" AProjectileBase::NetMulticast_OnDeactivated(): Velocity == %s !!!!!!") ,*this->ProjectileMovementComponent->Velocity.ToString()));
	UObjectPoolSystem::Get(GetGameInstance())->ReturnObject(TEXT("Projectile"), this);
	this->ParticleSystemComponent->SetTemplate(nullptr);

}

void AProjectileBase::NetMulticast_SetLifetime_Implementation(float NewValue)
{
	this->ObjectPoolSystemComponent->SetLifetime(NewValue);


}

void AProjectileBase::SetVelocity(float Speed, const FVector& Direction)
{
	this->ProjectileMovementComponent->Velocity = Speed * Direction;
	///GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" AProjectileBase::SetVelocity(): Velocity == %s !!!!!!"), *this->ProjectileMovementComponent->Velocity.ToString()));


}

void AProjectileBase::NetMulticast_ReturnObjectPool_Implementation()
{
	UObjectPoolSystem::Get(GetGameInstance())->ReturnObject(TEXT("Projectile"), this);

}
void AProjectileBase::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{
	if (HitResultArray.Num() == 0) return;
	for (auto& Element:HitResultArray)
	{
		if(this->CollisionDetectionComponent->GetAllIgnoredActor().Contains(Element.GetActor())==true) continue;
		this->CollisionDetectionComponent->AddIgnoredActor(Element.GetActor());
		ACharacterBase* Character = Cast<ACharacterBase>(Element.GetActor());

		if (Character == nullptr || this->DamageEffectSpecHandle.IsValid() == false) continue;
		Character->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*this->DamageEffectSpecHandle.Data.Get());
		//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("AProjectileBase::OnCollisionDetectionEnd(): Actor == %s "),*Character->GetName()));

	}

	NetMulticast_SpawnHitVFX(this->ProjectileDataAsset.ToString(),GetActorLocation());
	this->ObjectPoolSystemComponent->DeactivatedOwner();

}

