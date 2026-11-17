// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "AttributeSet/GAS_AttributeSet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetComponent.h"
#include "Component/CollisionDetectionComponent.h"
#include "Weapon/WeaponBase.h"
#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/CharacterDataAsset.h"



APlayerCharacter::APlayerCharacter()
{
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));


	this->AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	this->CameraComponent->SetupAttachment(this->SpringArmComponent);

	this->SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	this->SpringArmComponent->bDoCollisionTest = false;
	this->SpringArmComponent->TargetArmLength = 500.0f;
	this->SpringArmComponent->SocketOffset = FVector(0.0f);
	this->SpringArmComponent->bInheritYaw = true;
	this->SpringArmComponent->bInheritPitch = true;
	this->SpringArmComponent->bInheritRoll = true;
	this->SpringArmComponent->bUsePawnControlRotation = true;

	this->bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->SetIsReplicated(true);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetIsReplicated(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	GetCapsuleComponent()->SetIsReplicated(true);



}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	///GameInstance->GetAssetManager()->BindAssetLoadCompletionDelegate(this,TEXT("OnAssetLoadCompletion"));

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();


}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	Server_CancelAbility(Tag::Ability::Jump);
}

void APlayerCharacter::Server_SetWeaponOpacity_Implementation(float NewOpacity)
{
	if (Weapon == nullptr) return;
	Weapon->NetMulticast_SetMeshOpacity(NewOpacity);

	///GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("NetMulticast_SetWeaponOpacity(): NewOpacity == %f  !!!!"),NewOpacity));

}

void APlayerCharacter::NetMulticast_SetPlayerID_Implementation(int32 NewID)
{
	PlayerID = NewID;
}



void APlayerCharacter::ExecuteCollisionDetection()
{
	Super::ExecuteCollisionDetection();
	const FString ProfileName = TEXT("Weapon");
	const FVector StartLocation = GetWeapon()->GetMeshSlotLocation(TEXT("StartSlot"));
	const FVector EndLocation = GetWeapon()->GetMeshSlotLocation(TEXT("EndSlot"));
	const float Radius = 10.0f;
	GetCollisionDetectionComponent()->SphereTrace(StartLocation, EndLocation, Radius, ProfileName);
	OnCollisionDetectionEnd(GetCollisionDetectionComponent()->GetAllHitResult());

}

void APlayerCharacter::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{
	Super::OnCollisionDetectionEnd(HitResultArray);



}


void APlayerCharacter::EquipWeapon()
{
	//GetCurrentMontage()->
	//GetMesh()->GetAnimInstance()->Montage
}

void APlayerCharacter::UnequipWeapon()
{
}

