

#include "Weapon/WeaponBase.h"


#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"

#include "Component/CollisionDetectionComponent.h"



AWeaponBase::AWeaponBase()
{
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	this->StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));

	this->PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(this->CapsuleComponent);

	this->StaticMeshComponent->SetupAttachment(GetRootComponent());
	this->StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->StaticMeshComponent->SetRelativeLocation(FVector(0.0f,0.0f,-60.0f));
	//this->CapsuleComponent->InitCapsuleSize(this->Radius, this->Length * 0.5f);
	SetReplicates(true);
	//this->StaticMeshComponent->GetStaticMesh();
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AWeaponBase::GetCenterLocation()
{
	return this->StaticMeshComponent->GetSocketLocation(TEXT("CenterSlot"));
}

float AWeaponBase::GetWeaponRadius()
{
	return this->CapsuleComponent->GetUnscaledCapsuleRadius();
}

float AWeaponBase::GetWeaponLength()
{
	return this->CapsuleComponent->GetUnscaledCapsuleHalfHeight() * 2.0f;
}

void AWeaponBase::SetMeshLocation(const FVector& NewLocation)
{
	this->StaticMeshComponent->SetRelativeLocation(NewLocation);
}


void AWeaponBase::NetMulticast_SetMeshOpacity_Implementation(float NewOpacity)
{
	this->StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Opacity"), NewOpacity);

}

void AWeaponBase::SetMeshGlow(float NewValue)
{

	this->StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Glow"), NewValue);


}

void AWeaponBase::SetMeshGlowColor(const FVector& NewColor)
{

	this->StaticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("GlowColor"), NewColor);

}

void AWeaponBase::SetMeshOpacity(float NewOpacity)
{
	this->StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Opacity"), NewOpacity);
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("SetWeaponOpacity(): NewOpacity == %f  !!!!"), NewOpacity));
	//this->StaticMeshComponent->SetStaticMesh();
}

void AWeaponBase::ExecuteCollisionDetection()
{
	/*const FVector StartLocation = this->StaticMeshComponent->GetSocketLocation(TEXT("StartSlot"));
	const FVector EndLocation = this->StaticMeshComponent->GetSocketLocation(TEXT("EndSlot"));
	this->CollisionDetectionComponent->SphereTrace(StartLocation,EndLocation,50.0f,TEXT("PlayerCharacter"));

	OnCollisionDetectionEnd(this->CollisionDetectionComponent->GetAllHitResult());*/

}

void AWeaponBase::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{
	
}

FVector AWeaponBase::GetMeshSlotLocation(const FString& SlotName)
{
	if (this->StaticMeshComponent == nullptr) return FVector(0.0f);
	return this->StaticMeshComponent->GetSocketLocation(FName(SlotName));

}

