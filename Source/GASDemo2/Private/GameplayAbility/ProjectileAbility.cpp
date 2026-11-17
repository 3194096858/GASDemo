

#include "GameplayAbility/ProjectileAbility.h"


#include "Character/CharacterBase.h"
#include "Weapon/WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/CollisionDetectionComponent.h"
#include "Struct/GAS_GameplayEffectContext.h"
#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"
#include "DataAsset/CharacterDataAsset.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "ObjectPoolSystem/ObjectPoolSystem.h"
#include "Projectile/ProjectileBase.h"
#include "Controller/PlayerController/GAS_PlayerController.h"
#include "GameMode/GAS_GameMode.h"
#include "DataAsset/ProjectileDataAsset.h"
#include "GameplayTag/GameplayTag.h"
#include "GameplayEffect.h"
#include "Component/ObjectPoolSystemComponent.h"



void UProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//AddGameplayTag


}

void UProjectileAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);


}

void UProjectileAbility::Server_SpawnProjectile_Implementation(const FTransform& ObjectTransform)
{
	if (this->ProjectileDataAsset.IsNull() == true) return;
	UObject* AssetObject = GetGameInstance()->GetAssetManager()->GetAsset(this->ProjectileDataAsset.ToString());
	if (AssetObject == nullptr) return;

	UClass* DamageEffectClass = *GetCharacterAsset()->EffectClassMap.Find(Tag::Effect::ProjectileDamage);
	
	///GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" UProjectileAbility::Server_SpawnProjectile(): Size == %d !!!!!!"), UObjectPoolSystem::Get(GetGameInstance())->GetPoolSize(TEXT("Projectile"))));

	UProjectileDataAsset* ProjectileAsset = Cast<UProjectileDataAsset>(AssetObject);
	AActor* Actor = UObjectPoolSystem::Get(GetGameInstance())->GetObject(ProjectileAsset->ProjectileClass, TEXT("Projectile"), ObjectTransform);
	AProjectileBase* Projectile = Cast<AProjectileBase>(Actor);
	FGameplayEffectSpecHandle EffectSpecHandle;
	FGameplayEffectContextHandle EffectContextHandle;
	Projectile->SetVelocity(ProjectileAsset->MovementSpeed, GetCharacter()->GetActorForwardVector());
	Projectile->NetMulticast_SetLifetime(ProjectileAsset->Lifetime);
	Projectile->SetInstigator(GetCharacter());
	//Projectile->NetMulticast_SetHitVFX(this->ProjectileDataAsset.ToString());
	EffectSpecHandle = GetCharacter()->GetAbilitySystemComponent()->MakeOutgoingSpec(DamageEffectClass,1.0f,EffectContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(Tag::Effect::Data::ProjectileDamage, ProjectileAsset->Damage * -1);
	Projectile->Server_SetDamageEffectSpecHandle(EffectSpecHandle);

	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" UProjectileAbility::Server_SpawnProjectile(): Actor == %s !!!!!!"),*Actor->GetName()));
	Projectile->GetObjectPoolSystemComponent()->ActivatedOwner();

}
