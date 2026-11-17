
#include "GameplayCue/Static/HitReactionCue.h"
#include  "Character/CharacterBase.h"
#include "GameplayTag/GameplayTag.h"

#include "AssetManager/GAS_AssetManager.h"
#include "GameInstance/GAS_GameInstance.h"
#include "DataAsset/CharacterDataAsset.h"

void UHitReactionCue::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	if (EventType != EGameplayCueEvent::Executed) return;
	UCharacterDataAsset* Asset = GetCharacterAsset();
	if (Asset == nullptr) return;

	if (Parameters.EffectContext.GetHitResult() == nullptr) return;

	Server_SetReactionDirectionTag(Parameters.EffectContext.GetHitResult()->ImpactPoint);
	UAnimMontage** Montage = Asset->HitReactionMontageMap.Find(this->ReactionDirectionTag);
	if (Montage !=nullptr)
	{
		GetCharacter()->PlayAnimMontage(*Montage,this->MontagePlayRate);

	}


}

void UHitReactionCue::NetMulticast_SetReactionDirectionTag_Implementation(const FGameplayTag& NewTag)
{
	this->ReactionDirectionTag = NewTag;


}

void UHitReactionCue::Server_SetReactionDirectionTag_Implementation(const FVector& AttackImpactPoint)
{
	FGameplayTag Tag = Tag::ReactionDirection::Front;
	FVector DirectionVector =  AttackImpactPoint - GetCharacter()->GetActorLocation() ;
	DirectionVector = DirectionVector.GetSafeNormal();
	const float DotValue = FVector::DotProduct(DirectionVector, GetCharacter()->GetActorForwardVector());

	if (DotValue >= 0.5f)
	{
		Tag = Tag::ReactionDirection::Back;
	}

	if (DotValue <= 0.0f)
	{
		const FVector CrossValue = FVector::CrossProduct(DirectionVector, GetCharacter()->GetActorForwardVector());

		if (CrossValue.Z > 0.0f)
		{
			Tag = Tag::ReactionDirection::Right;
		}
		else
		{
			Tag = Tag::ReactionDirection::Left;

		}
	}
	NetMulticast_SetReactionDirectionTag(Tag);

//	GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("HandleGameplayCue: DotValue = %f "), DotValue));
	//GEngine->AddOnScreenDebugMessage(-1, 11.0f, FColor::Blue, FString::Printf(TEXT("HandleGameplayCue: Tag = %s "), *Tag.ToString()));

}
