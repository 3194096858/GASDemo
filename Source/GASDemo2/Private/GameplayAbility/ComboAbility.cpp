

#include "GameplayAbility/ComboAbility.h"
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

#include "DataAsset/ComboAbilityDataAsset.h"



void UComboAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	


}

void UComboAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo,bReplicateEndAbility,bWasCancelled);

	this->IgnoreActorArray.Empty();

}


int32 UComboAbility::GetMontageNumber()
{
	UComboAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UComboAbilityDataAsset>(Tag::Ability::Combo);
	if (Asset == nullptr) return 0;

	return Asset->MontageArray.Num();
}

UAnimMontage* UComboAbility::GetMontage(int32 Index)
{
	UComboAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UComboAbilityDataAsset>(Tag::Ability::Combo);
	if (Asset == nullptr) return nullptr;

	return Asset->MontageArray[Index];
}

float UComboAbility::GetComboInterval()
{
	UComboAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UComboAbilityDataAsset>(Tag::Ability::Combo);
	if (Asset == nullptr) return 0;

	return Asset->Interval;
}

int32 UComboAbility::GetCurrentComboNumber()
{

	UComboAbilityDataAsset* Asset = GetCharacterAsset()->GetAbilityAsset<UComboAbilityDataAsset>(Tag::Ability::Combo);
	if (Asset == nullptr || GetCurrentMontage() == nullptr) return 0;

	return Asset->MontageArray.Find(GetCurrentMontage()) + 1;
}

void UComboAbility::Server_ExecuteCollisionDetection_Implementation()
{
	if (GetCharacter()->HasAuthority() == false) return;
	//APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	/*const FString ProfileName = TEXT("Weapon");
	const FVector StartLocation = PlayerCharacter->GetWeapon()->GetMeshSlotLocation(TEXT("StartSlot"));
	const FVector EndLocation = PlayerCharacter->GetWeapon()->GetMeshSlotLocation(TEXT("EndSlot"));
	GetCharacter()->GetCollisionDetectionComponent()->SphereTrace(StartLocation, EndLocation, 10.0f,ProfileName);
	OnCollisionDetectionEnd(GetCharacter()->GetCollisionDetectionComponent()->GetAllHitResult());*/
	GetCharacter()->ExecuteCollisionDetection();
	OnCollisionDetectionEnd(GetCharacter()->GetCollisionDetectionComponent()->GetAllHitResult());
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" UComboAbility::Server_ExecuteCollisionDetection(): ")));

}

void UComboAbility::OnCollisionDetectionEnd(const TArray<FHitResult>& HitResultArray)
{
	ACharacterBase* Character = nullptr;
	UClass* EffectClass = nullptr;
	UCharacterDataAsset* Asset = GetCharacterAsset();
	if (Asset == nullptr) return;

	for (auto& Element : Asset->EffectClassMap)
	{
		if (Element.Key == Tag::Effect::ComboDamage)
		{
			EffectClass =  Element.Value;
		}
	}
	for (auto& Element : HitResultArray)
	{
		if (this->IgnoreActorArray.Contains(Element.GetActor()) == true) continue;
		Character = Cast<ACharacterBase>(Element.GetActor());
		if (EffectClass == nullptr || Character == nullptr || Character == GetCharacter()) continue;
		FGameplayCueParameters ComboCueParameters;
		FGameplayEffectContextHandle ContextHandle = GetCharacter()->GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = GetCharacter()->GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, 1.0f, ContextHandle);
		FGAS_GameplayEffectContext* EffectContext = static_cast<FGAS_GameplayEffectContext*>(ContextHandle.Get());
		EffectContext->AddInstigator(GetCharacter(), Element.GetActor());
		EffectContext->AddHitResult(Element);
		EffectContext->ComboEffectData.CurrentComboNumber = GetCurrentComboNumber();
		ComboCueParameters.EffectContext = ContextHandle;
		GetCharacter()->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), Character->GetAbilitySystemComponent());
		Character->GetAbilitySystemComponent()->ExecuteGameplayCue(Tag::Cue::Combo,ComboCueParameters);

		//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT(" UComboAbility::OnCollisionDetectionEnd(): Actor == %s"), *Element.GetActor()->GetName()));

		this->IgnoreActorArray.AddUnique(Element.GetActor());
	}
}
