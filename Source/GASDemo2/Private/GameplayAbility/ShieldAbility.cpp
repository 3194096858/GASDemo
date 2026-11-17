

#include "GameplayAbility/ShieldAbility.h"


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
#include "DataAsset/ShieldAbilityDataAsset.h"


void UShieldAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UShieldAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UShieldAbilityDataAsset>(Tag::Ability::Shield);
	this->DefenseIncrease = Asset->DefenseIncrease;

	Server_SetTimer();

}

void UShieldAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UShieldAbility::Server_SetTimer_Implementation()
{
	UShieldAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UShieldAbilityDataAsset>(Tag::Ability::Shield);
	float Duration = Asset->Duration;

	GetWorld()->GetTimerManager().ClearTimer(this->TimerHandle);
	GetWorld()->GetTimerManager().SetTimer
	(
		this->TimerHandle,
		[this]()
		{
		  EndAbility(GetCurrentAbilitySpecHandle(),CurrentActorInfo,GetCurrentActivationInfo(),true,true);
		  ///GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("Server_SetTimer(): EndAbility !!!")));

		}, 
		Duration,
		false
	);


}




