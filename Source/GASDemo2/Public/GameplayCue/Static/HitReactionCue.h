
#pragma once

#include "GameplayTag/GameplayTag.h"


#include "CoreMinimal.h"
#include "GameplayCue/Static/GameplayCueStaticBase.h"
#include "HitReactionCue.generated.h"



UCLASS()
class GASDEMO2_API UHitReactionCue : public UGameplayCueStaticBase
{
	GENERATED_BODY()

protected:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;

protected:
	FGameplayTag ReactionDirectionTag = Tag::ReactionDirection::Back;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MontagePlayRate = 1.0f;
protected:
	UFUNCTION(Server,Reliable)
	void Server_SetReactionDirectionTag(const FVector& AttackImpactPoint);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetReactionDirectionTag(const FGameplayTag& NewTag);

};
