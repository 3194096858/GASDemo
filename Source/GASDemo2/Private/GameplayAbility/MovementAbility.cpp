

#include "GameplayAbility/MovementAbility.h"


#include "Character/CharacterBase.h"
#include "Controller/PlayerController/GAS_PlayerController.h"


void UMovementAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (GetCharacter() == nullptr) return;
	const FRotator YawRotation = FRotator(0.0f, GetPlayerController()->GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardDirection, GetPlayerController()->MovementInputValue.Y);
	GetCharacter()->AddMovementInput(RightDirection, GetPlayerController()->MovementInputValue.X);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);


}
