

#include "AttributeSet/GAS_AttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameplayTag/GameplayTag.h"
#include "Component/GAS_AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/CharacterBase.h"
#include "Controller/PlayerController/GAS_PlayerController.h"
#include "Controller/AIController/GAS_AIController.h"
#include "Character/NPC.h"


UGAS_AttributeSet::UGAS_AttributeSet()
{
	
}



void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Defense, COND_None, REPNOTIFY_Always);


}

void UGAS_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute,NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.0f,GetMaxHealth());
	}
	if (Attribute == GetDefenseAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 9999.0f);
	}

}

void UGAS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwningActor());
	ANPC* NPC = Cast<ANPC>(GetOwningActor());
	AGAS_PlayerController* PlayerController = Cast<AGAS_PlayerController>(Character->GetController());
	

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		if (GetHealth() <= 0.0f)
		{
			if (PlayerController != nullptr)
			{
				PlayerController->Server_OnPlayerDied();
			}
			if (NPC != nullptr)
			{
				NPC->Server_OnDied();
			}
		}
		else
		{
			FGameplayCueParameters Parameters;
			Parameters.EffectContext = Data.EffectSpec.GetEffectContext();
			if (PlayerController != nullptr)
			{
				GetOwningAbilitySystemComponent()->ExecuteGameplayCue(Tag::Cue::HitReaction::PlayerCharacter, Parameters);
			}
			if (NPC != nullptr)
			{
				GetOwningAbilitySystemComponent()->ExecuteGameplayCue(Tag::Cue::HitReaction::NPC, Parameters);

			}
		}
		if (PlayerController != nullptr)
		{
			PlayerController->Server_UpdatePlayerHealthBar();
		}
		if (NPC != nullptr)
		{
			NPC->Server_UpdateHealthBar();
		}
	}
	
}


void UGAS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet,Health,OldData);

	///SetHealth(FMath::Clamp(Health.GetCurrentValue(), 0.0f, GetMaxHealth()));
	

}

void UGAS_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxHealth, OldData);

}

void UGAS_AttributeSet::OnRep_Attack(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Attack, OldData);

}

void UGAS_AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Strength, OldData);

}

void UGAS_AttributeSet::OnRep_Defense(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Defense, OldData);

}
