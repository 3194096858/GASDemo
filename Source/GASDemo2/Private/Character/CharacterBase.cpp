

#include "Character/CharacterBase.h"
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
#include "GameplayTag/GameplayTag.h"
#include "Component/ObjectPoolSystemComponent.h"
#include "DataAsset/CharacterDataAsset.h"
#include "DataAsset/ProjectileDataAsset.h"
#include "GameMode/GAS_GameMode.h"



ACharacterBase::ACharacterBase()
{
	this->AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	this->AttributeSet = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("AttributeSet"));
	this->WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));
	this->ObjectPoolSystemComponent = CreateDefaultSubobject<UObjectPoolSystemComponent>(TEXT("ObjectPoolSystemComponent"));


	this->AbilitySystemComponent->SetIsReplicated(true);
	
	this->PrimaryActorTick.bCanEverTick = true;


	this->WidgetComponent->SetupAttachment(GetRootComponent());
	this->WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	this->WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	this->WidgetComponent->SetDrawSize(FVector2D(200.0f, 40.0f));
	this->WidgetComponent->SetIsReplicated(true);

	GetCapsuleComponent()->SetIsReplicated(true);
	SetReplicates(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	AGAS_GameMode* GameMode = Cast<AGAS_GameMode>(UGameplayStatics::GetGameMode(this));

	GameInstance->GetAssetManager()->BindAssetLoadCompletionDelegate(this,TEXT("OnAssetLoadCompletion"));
	
	GameInstance->GetAssetManager()->LoadAsset(this->CharacterDataAsset);
	GameInstance->GetAssetManager()->LoadAsset(this->ProjectileDataAsset);
	if (GameMode != nullptr)
	{
		GameMode->BindPlayerLoginDelegate(this,TEXT("OnPlayerLogin"));

	}
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&ACharacterBase::OnMontageEnd);
	GetMesh()->GetAnimInstance()->OnMontageStarted.AddDynamic(this, &ACharacterBase::OnMontageStart);

}

void ACharacterBase::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	AGAS_GameMode* GameMode = Cast<AGAS_GameMode>(UGameplayStatics::GetGameMode(this));

	GameInstance->GetAssetManager()->UnbindAssetLoadCompletionDelegate(this);
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveAll(this);
	GetMesh()->GetAnimInstance()->OnMontageStarted.RemoveAll(this);
	if (GameMode != nullptr)
	{
		GameMode->UnbindPlayerLoginDelegate(this);

	}

}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	

}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();


}

void ACharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

}

void ACharacterBase::Server_ActivateAbility_Implementation(const FGameplayTag& AbilityTag)
{
	this->AbilitySystemComponent->TryActivateAbility(GetAbilitySpecHandle(AbilityTag));

}

void ACharacterBase::NetMulticast_EnableCollision_Implementation()
{
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void ACharacterBase::NetMulticast_DisableCollision_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACharacterBase::Server_InitializeAbility_Implementation()
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	Server_GiveAllAbility();
}

void ACharacterBase::ActivateAbility(const FGameplayTag& AbilityTag)
{
	this->AbilitySystemComponent->TryActivateAbility(GetAbilitySpecHandle(AbilityTag));


}

void ACharacterBase::Server_InitializeAttribute_Implementation()
{
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* Asset = GameInstance->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());

	if (Asset == nullptr) return;
	UCharacterDataAsset* DataAsset = Cast<UCharacterDataAsset>(Asset);
	auto EffectClass = DataAsset->EffectClassMap.Find(Tag::Effect::AttributeInitialization);

	checkf(EffectClass,TEXT("ACharacterBase::Server_InitializeAttribute(): EffectClass == nullptr !!!!"));

	FGameplayEffectContextHandle ContextHandle = this->AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = this->AbilitySystemComponent->MakeOutgoingSpec(*EffectClass, 1.0f, ContextHandle);

	this->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

}

void ACharacterBase::Server_GiveAllAbility_Implementation()
{
	UGAS_GameInstance* GameInstance = Cast<UGAS_GameInstance>(GetGameInstance());
	UObject* AssetObject = GameInstance->GetAssetManager()->GetAsset(this->CharacterDataAsset.ToString());
	checkf(AssetObject ,TEXT("ACharacterBase::Server_GiveAllAbility(): AssetObject == nullptr !!!!"));
	UCharacterDataAsset* Asset = Cast<UCharacterDataAsset>(AssetObject);
	for (auto& Element : Asset->AbilityClassMap)
	{
		if (this->AbilitySystemComponent->FindAbilitySpecFromClass(Element.Value) != nullptr) continue;
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Element.Value);
		FGameplayAbilitySpecHandle SpecHandle = this->AbilitySystemComponent->GiveAbility(Spec);
		this->AbilitySpecHandleMap.Add(Element.Key, SpecHandle);

	}

	///GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("ACharacterBase::Server_GiveAllAbility(): ")));

}

void ACharacterBase::NetMulticast_SetMeshOpacity_Implementation(float NewOpacity)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Opacity"), NewOpacity);

}

void ACharacterBase::NetMulticast_SetMeshGlow_Implementation(float NewValue)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Glow"), NewValue);

}

void ACharacterBase::NetMulticast_SetMeshGlowColor_Implementation(const FVector& NewColor)
{
	GetMesh()->SetVectorParameterValueOnMaterials(TEXT("GlowColor"), NewColor);

}



void ACharacterBase::Server_CancelAbility_Implementation(const FGameplayTag& AbilityTag)
{
	FGameplayAbilitySpecHandle* SpecHandle = this->AbilitySpecHandleMap.Find(AbilityTag);
	if (SpecHandle == nullptr) return;
	this->AbilitySystemComponent->CancelAbilityHandle(*SpecHandle);


}


void ACharacterBase::Client_CancelAbility_Implementation(const FGameplayTag& AbilityTag)
{
	FGameplayAbilitySpecHandle* SpecHandle = this->AbilitySpecHandleMap.Find(AbilityTag);
	if (SpecHandle == nullptr) return;
	this->AbilitySystemComponent->CancelAbilityHandle(*SpecHandle);


}

FString ACharacterBase::GetAbilityName(const FGameplayAbilitySpecHandle& SpecHandle)
{
	const FGameplayTag* Tag = this->AbilitySpecHandleMap.FindKey(SpecHandle);
	checkf(Tag,TEXT("ACharacterBase::GetAbilityName(): Tag == nullptr !!!"));
	FString TagString = Tag->ToString();
	FString Left;
	FString Right;
	TagString.Split(TEXT(".Ability."), &Left, &Right);
	return Right;
}

TArray<FGameplayAbilitySpecHandle> ACharacterBase::GetAllCooldownAbilitySpecHandle()
{
	TArray<FGameplayAbilitySpecHandle> Array;
	for(auto& Element:this->AbilitySpecHandleMap)
	{
		FGameplayAbilitySpec* Spec = GetAbilitySystemComponent()->FindAbilitySpecFromHandle(Element.Value);
		if (Spec->Ability->AbilityTags.HasTagExact(Tag::Ability::Cooldown))
		{
			Array.AddUnique(Element.Value);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("ACharacterBase::Server_GiveAllAbility(): Number == %d !!!"),Array.Num()));

	return Array;
}

void ACharacterBase::ExecuteCollisionDetection()
{
	
}

void ACharacterBase::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{

	return this->AbilitySystemComponent;
}


void ACharacterBase::OnAssetLoadCompletion(const FString& AssetPath)
{

}

void ACharacterBase::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{

}

void ACharacterBase::OnMontageStart(UAnimMontage* Montage)
{

}

void ACharacterBase::OnPlayerLogin(APlayerController* PlayerController)
{


}



FGameplayAbilitySpecHandle ACharacterBase::GetAbilitySpecHandle(const FGameplayTag& AbilityTag)
{
	FGameplayAbilitySpecHandle* SpecHandle = this->AbilitySpecHandleMap.Find(AbilityTag);
	///if (SpecHandle == nullptr) return FGameplayAbilitySpecHandle();
	checkf(SpecHandle,TEXT("this->AbilitySpecHandleMap.Find(AbilityTag) == nullptr"));
	return *SpecHandle;
}
