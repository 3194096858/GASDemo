#pragma once
#include "GameplayTag/GameplayTag.h"
//#include "GameplayEff
#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "GAS_GameplayEffectContext.generated.h"


USTRUCT(BlueprintType)
struct FComboEffectData
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	int32 CurrentComboNumber = 0;

};
//
//
//USTRUCT(BlueprintType)
//struct FHitReactionEffectData
//{
//	GENERATED_BODY()
//	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
//	FGameplayTag AttackDirectionTag;
//
//};


USTRUCT(BlueprintType)
struct FGAS_GameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	FComboEffectData ComboEffectData;
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	};

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override
	{
		Super::NetSerialize(Ar,Map,bOutSuccess);
		Ar << ComboEffectData.CurrentComboNumber;
		bOutSuccess = true;
		return true;
	};
	virtual FGameplayEffectContext* Duplicate() const override
	{
		FGAS_GameplayEffectContext* NewContext = new FGAS_GameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

};


template<>
struct TStructOpsTypeTraits<FGAS_GameplayEffectContext> : public TStructOpsTypeTraitsBase2<FGAS_GameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};