#pragma once

// CHARACTER -------

UENUM(BlueprintType)
enum class EStats : uint8
{
	Ess_HP UMETA(DisplayNmae="HP"),
	Ess_SP UMETA(DisplayNmae="SP"),
	Ess_Stamina UMETA(DisplayNmae="Stamina")
};

UENUM(BlueprintType)
enum class  EActionStates : uint8
{
	Eas_Unocuppied UMETA(Displayname="Unocuppied"),
	Eas_Dead UMETA(Displayname="Dead"),
	Eas_Attacking UMETA(Displayname="Attacking"),
	Eas_Guarding UMETA(DisplayNamee="Guarding"),
	Eas_Casting UMETA(Displayname="Casting"),
	Eas_Dodging UMETA(DisplayNmae="Dodging"),
	Eas_Equipping UMETA(DisplayNmae="Equipping"),
	Eas_JumpingOrFalling UMETA(DisplayNmae="Jumping/Falling"),
	Eas_Knocked UMETA(DisplayNmae="Knocked"),
	Eas_Riding UMETA(DisplayName="Riding")
};

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	Ect_None UMETA(DisplayNmae="None"),
	Ect_Sword UMETA(DisplayNmae="Sword"),
	Ect_GreatSword UMETA(DisplayNmae="GreatSword"),
	Ect_DualSword UMETA(DisplayNmae="DualSword"),
	Ect_Bow UMETA(DisplayNmae="Bow"),
	Ect_Staff UMETA(DisplayNmae="Staff")
	
};

//* Karakter Hızları */
UENUM(BlueprintType)
enum class EMovementModes : uint8
{
	Emm_Sprinting UMETA(DisplayNmae="Sprinting"),
	Emm_Running UMETA(DisplayNmae="Running"),
	Emm_Walking UMETA(DisplayNmae="Walking")
};

// ITEM

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Eit_None UMETA(DisplayNmae="None"),
	Eit_Craft UMETA(DisplayNmae="Craft"),
	Eit_Weapon UMETA(DisplayNmae="Weapon"),
	Eit_Armor UMETA(DisplayNmae="Armor")
};

// SKİLL-ATTACKS

/**
 * Basic Damage herhangibir hitreaction koşturmaz
 * 
 * Damage hitreaction koşturur savrulma gibi
 * 
 * Heavy Damage ise knockoutlar
 */
UENUM(BlueprintType)
enum class EDamageTypes : uint8
{
	Edt_BasicDamage UMETA(DisplayNmae="BasicDamage"),
	Edt_Damage UMETA(DisplayNmae="Damage"),
	Edt_HeavyDamage UMETA(DisplayNmae="HeavyDamage")
};

UENUM(BlueprintType)
enum class ESkillDamageEffectTypes : uint8
{
	Esdet_NoEffect UMETA(DisplayNmae="NoEffect"),
	Esdet_Stun UMETA(DisplayNmae="Stun"),
	Esdet_Fire UMETA(DisplayNmae="Fire"),
	Esdet_Froze UMETA(DisplayNmae="Froze"),
	Esdet_Poison UMETA(DisplayNmae="Poison")
};

UENUM(BlueprintType)
enum class EDamageActorType : uint8
{
	Edat_AttachedDamageActor UMETA(DisplayNmae="AttachedDamageActor"),
	Edat_AttachedAuraActor UMETA(DisplayNmae="AttachedAuraActor"), // kullanmayacaz bu projede
	Edat_AttachedLocationDamageActor UMETA(DisplayNmae="AttachedLocationDamageActor"),
	Edat_AreaDirectDamage UMETA(DisplayNmae="AreaDirectDamage"),
	Edat_ProjectileDamageActor UMETA(DisplayNmae="ProjectileDamageActor")
};

// AI


UENUM(BlueprintType)
enum class EAIPerceptions : uint8
{
	EAI_None UMETA(DisplayName="None"),
	EAI_Sight UMETA(DisplayName="Sight"),
	EAI_Hearing UMETA(DisplayName="Hearing"),
	EAI_Damage UMETA(DisplayName="Damage")
};

UENUM(BlueprintType)
enum class C_EAIStates : uint8
{
	EAS_Passive UMETA(DisplayName="Passive"),
	EAS_CloseCombat UMETA(DisplayName="CloseCombat"),
	EAS_LongDistanceCombat UMETA(DisplayName="LongDistanceCombat"),
	EAS_Chasing UMETA(DisplayName="Chasing"),
	EAS_Waiting UMETA(DisplayName="Waiting")
};
