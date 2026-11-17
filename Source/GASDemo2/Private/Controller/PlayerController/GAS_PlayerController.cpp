
#include "Controller/PlayerController/GAS_PlayerController.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "AttributeSet/GAS_AttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameplayTagContainer.h"
#include "GameplayTag/GameplayTag.h"
#include "Character/PlayerCharacter.h"
#include "GameInstance/GAS_GameInstance.h"
#include "AssetManager/GAS_AssetManager.h"
#include "DataAsset/CharacterDataAsset.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"


#include "DataAsset/ProjectileDataAsset.h"




void AGAS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	GameInstance->GetAssetManager()->BindAssetLoadCompletionDelegate(this, TEXT("OnCharacterAssetLoadCompletion"));


}

void AGAS_PlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	GameInstance->GetAssetManager()->UnbindAssetLoadCompletionDelegate(this);
	UObjectPoolSystem::Get(GetGameInstance())->ClearAllPool();


}

void AGAS_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGAS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UInputDataAsset* InputDataAsset = GameInstance->GetAssetManager()->GetInputDataAsset();

	if (InputDataAsset == nullptr) return;
	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	UEnhancedInputComponent* Component = Cast<UEnhancedInputComponent>(this->InputComponent);

	if (System == nullptr || Component == nullptr) return;

	for (auto& Element: GameInstance->GetAssetManager()->GetInputDataAsset()->InputMappingContextArray)
	{
		System->AddMappingContext(Element,0);
		//Element->Add
	}
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Jump),ETriggerEvent::Started,this,&AGAS_PlayerController::OnJumpAbilityActivated);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Movement), ETriggerEvent::Triggered, this, &AGAS_PlayerController::OnMovementAbilityActivated);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Dash), ETriggerEvent::Started, this, &AGAS_PlayerController::OnDashAbilityActivated);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Projectile), ETriggerEvent::Started, this, &AGAS_PlayerController::OnProjectileAbilityActivated);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Shield), ETriggerEvent::Started, this, &AGAS_PlayerController::OnShieldAbilityActivated);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Input::Look), ETriggerEvent::Triggered, this, &AGAS_PlayerController::OnLook);
	Component->BindAction(InputDataAsset->GetInputAction(Tag::Ability::Combo), ETriggerEvent::Started, this, &AGAS_PlayerController::OnComboAbilityActivated);


}

void AGAS_PlayerController::Server_InitializeCharacterAbility_Implementation()
{

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	if (PlayerCharacter == nullptr) return;
	PlayerCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(GetCharacter(), GetCharacter());
	PlayerCharacter->Server_GiveAllAbility();
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("AGAS_PlayerController::OnCharacterAssetLoadCompletion(): 33333333")));



}

void AGAS_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	/*UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	GameInstance->GetAssetManager()->LoadAsset(this->CharacterDataAsset);
	GameInstance->GetAssetManager()->LoadAsset(this->ProjectileDataAsset);
*/

}


void AGAS_PlayerController::Server_InitializeCharacterAttribute_Implementation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	if (PlayerCharacter == nullptr) return;

	PlayerCharacter->Server_InitializeAttribute();

	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("Server_InitializeCharacterAttribute() !!!!")));

}

void AGAS_PlayerController::Server_UpdateCharacterMeshOpacity_Implementation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());

	if (PlayerCharacter == nullptr) return;
	static float Opacity = 1.0f;

	Opacity = Opacity - 0.01f;
	PlayerCharacter->NetMulticast_SetMeshOpacity(Opacity);

	if (Opacity <= 0.0f)
	{
		Opacity = 1.0f;
		GetWorld()->GetTimerManager().ClearTimer(this->CharacterMeshOpacityTimerHandle);

	}


}

void AGAS_PlayerController::OnLook(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddYawInput(InputValue.X);
	AddPitchInput(InputValue.Y * -1.0f);


}

void AGAS_PlayerController::OnJumpAbilityActivated()
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetCharacter());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Jump;


	PlayerCharacter->Server_ActivateAbility(Tag);

	//PlayerCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(Tag.GetSingleTagContainer());
}



void AGAS_PlayerController::OnMovementAbilityActivated(const FInputActionValue& Value)
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetCharacter());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Movement;
	this->MovementInputValue = Value.Get<FVector2D>();
	PlayerCharacter->Server_ActivateAbility(Tag);

}


void AGAS_PlayerController::OnDashAbilityActivated()
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetPawn());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Dash;
	PlayerCharacter->Server_ActivateAbility(Tag);
}


void AGAS_PlayerController::OnProjectileAbilityActivated()
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetCharacter());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Projectile;
	PlayerCharacter->Server_ActivateAbility(Tag);



	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, TEXT("OnProjectileAbilityActivated"));

}


void AGAS_PlayerController::OnShieldAbilityActivated()
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetPawn());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Shield;
	PlayerCharacter->Server_ActivateAbility(Tag);
}

void AGAS_PlayerController::OnComboAbilityActivated()
{

	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(GetCharacter());
	if (PlayerCharacter == nullptr) return;
	FGameplayTag Tag = Tag::Ability::Combo;
	PlayerCharacter->Server_ActivateAbility(Tag);


}

void AGAS_PlayerController::OnCharacterAssetLoadCompletion(const FString& AssetPath)
{
	if (AssetPath == this->CharacterDataAsset.ToString())
	{
		Server_InitializeCharacterAbility();
		Server_InitializeCharacterAttribute();
		OnCharacterAbilityInitializeCompletion();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("AGAS_PlayerController::OnCharacterAssetLoadCompletion(): 222222222")));

}

void AGAS_PlayerController::Server_UpdatePlayerHealthBar_Implementation()
{

	UpdatePlayerHealthBar();

}

void AGAS_PlayerController::UpdatePlayerHealthBar_Implementation()
{


}

void AGAS_PlayerController::Server_OnPlayerRespawn_Implementation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	PlayerCharacter->Server_CancelAbility(Tag::Ability::Death);
	PlayerCharacter->Server_SetWeaponOpacity(1.0f);
	PlayerCharacter->NetMulticast_SetMeshOpacity(1.0f);
	PlayerCharacter->NetMulticast_SetMeshGlowColor(FVector(0.0f));
	PlayerCharacter->NetMulticast_SetMeshGlow(0.0f);
	PlayerCharacter->NetMulticast_EnableCollision();

	PlayerCharacter->SetActorLocation(FVector(0.0f));
	Server_InitializeCharacterAttribute();
	OnPlayerRespawn();

}

void AGAS_PlayerController::UpdatePlayerRespawnCountdown_Implementation()
{
	if (this->PlayerRespawnTimeleft == 0)
	{
		Server_OnPlayerRespawn();
		GetWorld()->GetTimerManager().ClearTimer(this->PlayerRespawnTimerHandle);
		this->PlayerRespawnTimeleft = 30;
		return;
	}
	this->PlayerRespawnTimeleft--;
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("UpdatePlayerRespawnCountdown(): %d !!!!"), this->PlayerRespawnTimeleft));
	if (this->PlayerRespawnTimeleft == 20)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
		PlayerCharacter->NetMulticast_SetMeshGlowColor(FVector(1.0f));
		GetWorld()->GetTimerManager().SetTimer(this->CharacterMeshOpacityTimerHandle, this, &AGAS_PlayerController::UpdateCharacterMeshOpacity, 0.05f, true);

	}

}

void AGAS_PlayerController::OnPlayerDied_Implementation()
{

}

void AGAS_PlayerController::Server_OnPlayerDied_Implementation()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(this->PlayerRespawnTimerHandle) == true) return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	PlayerCharacter->Server_SetWeaponOpacity(0.0f);
	GetWorld()->GetTimerManager().SetTimer(this->PlayerRespawnTimerHandle,this,&AGAS_PlayerController::UpdatePlayerRespawnCountdown,1.0f,true,1.0f);
	PlayerCharacter->ActivateAbility(Tag::Ability::Death);
	PlayerCharacter->NetMulticast_DisableCollision();

	OnPlayerDied();

}


void AGAS_PlayerController::OnPlayerRespawn_Implementation()
{
	
}

void AGAS_PlayerController::UpdateCharacterMeshOpacity()
{
	Server_UpdateCharacterMeshOpacity();

}

void AGAS_PlayerController::OnCharacterAbilityInitializeCompletion_Implementation()
{


}
