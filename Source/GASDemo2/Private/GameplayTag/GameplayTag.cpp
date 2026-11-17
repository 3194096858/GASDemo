
#include "GameplayTag/GameplayTag.h"


namespace Tag
{
	namespace Ability
	{
		UE_DEFINE_GAMEPLAY_TAG(Dash, "Tag.Ability.Dash");
		UE_DEFINE_GAMEPLAY_TAG(Combo, "Tag.Ability.Combo");
		UE_DEFINE_GAMEPLAY_TAG(Jump, "Tag.Ability.Jump");
		UE_DEFINE_GAMEPLAY_TAG(Movement, "Tag.Ability.Movement");
		UE_DEFINE_GAMEPLAY_TAG(HitReaction, "Tag.Ability.HitReaction");
		UE_DEFINE_GAMEPLAY_TAG(Projectile, "Tag.Ability.Projectile");
		UE_DEFINE_GAMEPLAY_TAG(Death, "Tag.Ability.Death");
		UE_DEFINE_GAMEPLAY_TAG(Shield, "Tag.Ability.Shield");
		UE_DEFINE_GAMEPLAY_TAG(Passive, "Tag.Ability.Passive");
		UE_DEFINE_GAMEPLAY_TAG(Cooldown, "Tag.Ability.Cooldown");

	}
	namespace Effect
	{
		UE_DEFINE_GAMEPLAY_TAG(ComboDamage, "Tag.Effect.ComboDamage");
		UE_DEFINE_GAMEPLAY_TAG(ProjectileDamage, "Tag.Effect.ProjectileDamage");
		UE_DEFINE_GAMEPLAY_TAG(BurningDamage, "Tag.Effect.BurningDamage");
		UE_DEFINE_GAMEPLAY_TAG(AttributeInitialization, "Tag.Effect.AttributeInitialization");
		UE_DEFINE_GAMEPLAY_TAG(UpdateDefense, "Tag.Effect.UpdateDefense");

		namespace Cooldown
		{
			UE_DEFINE_GAMEPLAY_TAG(Dash, "Tag.Effect.Cooldown.Dash");
			UE_DEFINE_GAMEPLAY_TAG(Projectile, "Tag.Effect.Cooldown.Projectile");
			UE_DEFINE_GAMEPLAY_TAG(Shield, "Tag.Effect.Cooldown.Shield");
		}

		namespace Data
		{
			UE_DEFINE_GAMEPLAY_TAG(ProjectileDamage, "Tag.Effect.Data.ProjectileDamage");
			UE_DEFINE_GAMEPLAY_TAG(BurningDamage, "Tag.Effect.Data.BurningDamage");
			UE_DEFINE_GAMEPLAY_TAG(ShieldDefense, "Tag.Effect.Data.ShieldDefense");

		}

	}
	namespace Cue
	{
		UE_DEFINE_GAMEPLAY_TAG(Dash, "GameplayCue.Dash");
		UE_DEFINE_GAMEPLAY_TAG(Combo, "GameplayCue.Combo");
		UE_DEFINE_GAMEPLAY_TAG(Projectile, "GameplayCue.Projectile");
		UE_DEFINE_GAMEPLAY_TAG(Shield, "GameplayCue.Shield");
		UE_DEFINE_GAMEPLAY_TAG(Burning, "GameplayCue.Burning");
		namespace HitReaction
		{
			UE_DEFINE_GAMEPLAY_TAG(PlayerCharacter, "GameplayCue.HitReaction.PlayerCharacter");
			UE_DEFINE_GAMEPLAY_TAG(NPC, "GameplayCue.HitReaction.NPC");

		}

	}
	namespace Event
	{
		UE_DEFINE_GAMEPLAY_TAG(OnExecuteCollisionDetection, "Tag.Event.OnExecuteCollisionDetection");
		UE_DEFINE_GAMEPLAY_TAG(OnProjectileLaunch, "Tag.Event.OnProjectileLaunch");
		UE_DEFINE_GAMEPLAY_TAG(OnReceiveAttack, "Tag.Event.OnReceiveAttack");


	}
	namespace Character
	{
		UE_DEFINE_GAMEPLAY_TAG(Quinn, "Tag.Character.Quinn");
		//UE_DEFINE_GAMEPLAY_TAG(Boris, "Tag.Character.Boris");

	}
	
	namespace Input
	{
		UE_DEFINE_GAMEPLAY_TAG(Look, "Tag.Input.Look");
		UE_DEFINE_GAMEPLAY_TAG(SeathingSword, "Tag.Input.SeathingSword");
		UE_DEFINE_GAMEPLAY_TAG(WithdrwingSword, "Tag.Input.WithdrwingSword");


	}

	namespace ReactionDirection
	{
		UE_DEFINE_GAMEPLAY_TAG(Front, "Tag.ReactionDirection.Front");
		UE_DEFINE_GAMEPLAY_TAG(Back, "Tag.ReactionDirection.Back");
		UE_DEFINE_GAMEPLAY_TAG(Left, "Tag.ReactionDirection.Left");
		UE_DEFINE_GAMEPLAY_TAG(Right, "Tag.ReactionDirection.Right");
	}
}

