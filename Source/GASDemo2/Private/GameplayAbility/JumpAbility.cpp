#include "GameplayAbility/JumpAbility.h"

#include "Character/CharacterBase.h"



void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);

	ACharacterBase* Character = Cast<ACharacterBase>(GetAvatarActorFromActorInfo());
	if (Character == nullptr) return;
	Character->Jump();


	///EndAbility(Handle, ActorInfo, ActivationInfo, true, false);



}
