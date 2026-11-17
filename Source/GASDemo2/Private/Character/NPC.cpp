

#include "Character/NPC.h"

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
#include "DataAsset/NPCDataAsset.h"
#include "DataAsset/CharacterDataAsset.h"
#include "Controller/AIController/GAS_AIController.h"
#include "Component/ObjectPoolSystemComponent.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"


ANPC::ANPC()
{
	this->AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	GetCharacterMovement()->MaxWalkSpeed = 30.0f;
	GetCharacterMovement()->SetIsReplicated(true);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetIsReplicated(true);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	GetCapsuleComponent()->SetIsReplicated(true);



}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	this->ObjectPoolSystemComponent->ActivationDeLegate.BindUObject(this, &ANPC::OnActivated);
	this->ObjectPoolSystemComponent->DeactivationDeLegate.BindUObject(this, &ANPC::OnDeactivated);
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Server_InitializeAbility();
	Server_InitializeAttribute();

}

void ANPC::Server_RunBehaviorTree_Implementation()
{
	AGAS_AIController* AIController = Cast<AGAS_AIController>(GetController());

	AIController->Server_RunBehaviorTree();



}

void ANPC::NetMulticast_PlayRespawnMontage_Implementation(float PlayRate)
{
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* AssetObject = GameInstance->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());
	checkf(AssetObject, TEXT("ANPC::NetMulticast_PlayRespawnMontage(): AssetObject == nullptr !!!!"));
	UNPCDataAsset* Asset = Cast<UNPCDataAsset>(AssetObject);
	checkf(Asset->RespawnMontage,TEXT("ANPC::NetMulticast_PlayRespawnMontage(): Asset->RespawnMontage == nullptr !!!!"));
	PlayAnimMontage(Asset->RespawnMontage,PlayRate);
///	GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("  ANPC::NetMulticast_PlayRespawnMontage(): Actor == %s !!!!!!"), *GetName()));


}

void ANPC::UpdateHealthBar_Implementation()
{

}


void ANPC::Server_UpdateHealthBar_Implementation()
{
	UpdateHealthBar();

}


void ANPC::Server_Respawn_Implementation()
{
	Server_CancelAbility(Tag::Ability::Death);
	///
	NetMulticast_PlayRespawnMontage();
	Server_InitializeAttribute();
	OnRespawn();

}

void ANPC::Deactivated()
{
	this->ObjectPoolSystemComponent->DeactivatedOwner();

}

void ANPC::ExecuteCollisionDetection()
{
	Super::ExecuteCollisionDetection();
	const FString ProfileName = TEXT("NPC");
	const FVector StartLocation = GetMesh()->GetSocketLocation(TEXT("RightHandSlot"));
	const FVector EndLocation = GetMesh()->GetSocketLocation(TEXT("RightHandSlot"));
	const float Radius = 20.0f;
	GetCollisionDetectionComponent()->SphereTrace(StartLocation, EndLocation, Radius, ProfileName);
	OnCollisionDetectionEnd(GetCollisionDetectionComponent()->GetAllHitResult());

}

void ANPC::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{
	Super::OnCollisionDetectionEnd(HitResultArray);

}
void ANPC::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();


}

void ANPC::Server_OnDied_Implementation()
{

	OnDied();
	ActivateAbility(Tag::Ability::Death);


}
void ANPC::OnAssetLoadCompletion(const FString& AssetPath)
{
	Super::OnAssetLoadCompletion(AssetPath);
	if (AssetPath == this->CharacterDataAsset.ToString())
	{
		Server_RunBehaviorTree();

	}

	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("  ANPC::OnAssetLoadCompletion: Actor2222222222!!!!!!")));

}


void ANPC::OnDied_Implementation()
{

}

void ANPC::NetMulticast_OnActivated_Implementation()
{
	GetCharacterMovement()->GravityScale = 1.0f;
	SetActorHiddenInGame(false);

}

void ANPC::NetMulticast_OnDeactivated_Implementation()
{
	SetActorLocation(FVector(0.0f, 0.0f, 1000.0f));
	this->CollisionDetectionComponent->RemoveAllIgnoredActor();
	UObjectPoolSystem::Get(GetGameInstance())->ReturnObject(TEXT("Zombie"), this);
	GetCharacterMovement()->GravityScale = 0.0f;
	Server_InitializeAttribute();
	Server_CancelAbility(Tag::Ability::Death);
	Server_UpdateHealthBar();
	SetActorHiddenInGame(true);


}




void ANPC::OnRespawn_Implementation()
{

}

void ANPC::OnActivated()
{
	AGAS_AIController* AIController = Cast<AGAS_AIController>(GetController());
	AIController->Server_ResumeBehaviorTree();
	NetMulticast_EnableCollision();
	NetMulticast_PlayRespawnMontage();

	NetMulticast_OnActivated();

}

void ANPC::OnDeactivated()
{
	AGAS_AIController* AIController = Cast<AGAS_AIController>(GetController());
	AIController->Server_PauseBehaviorTree();

	NetMulticast_DisableCollision();
	NetMulticast_OnDeactivated();

}


void ANPC::OnMontageStart(UAnimMontage* Montage)
{
	Super::OnMontageStart(Montage);
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* AssetObject = GameInstance->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());
	checkf(AssetObject, TEXT("ANPC::NetMulticast_PlayRespawnMontage(): AssetObject == nullptr !!!!"));
	UNPCDataAsset* Asset = Cast<UNPCDataAsset>(AssetObject);

	if (Asset->RespawnMontage == Montage)
	{
		AGAS_AIController* AIController = Cast<AGAS_AIController>(GetController());
		AIController->Server_PauseBehaviorTree();
		NetMulticast_DisableCollision();

	}

}


void ANPC::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	Super::OnMontageEnd(Montage,bInterrupted);
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* AssetObject = GameInstance->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());
	checkf(AssetObject, TEXT("ANPC::NetMulticast_PlayRespawnMontage(): AssetObject == nullptr !!!!"));
	UNPCDataAsset* Asset = Cast<UNPCDataAsset>(AssetObject);

	if (Asset->RespawnMontage == Montage)
	{
		AGAS_AIController* AIController = Cast<AGAS_AIController>(GetController());
		AIController->Server_ResumeBehaviorTree();

		NetMulticast_EnableCollision();

	}

}

void ANPC::OnPlayerLogin(APlayerController* PlayerController)
{
	Super::OnPlayerLogin(PlayerController);
	Server_UpdateHealthBar();

}