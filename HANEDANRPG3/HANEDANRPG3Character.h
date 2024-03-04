// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/Enums.h"
#include "Interfaces/InteractInterface.h"
#include "HANEDANRPG3Character.generated.h"


class ADamageActor;
class ABaseWeapon;

UCLASS(config=Game)
class AHANEDANRPG3Character : public ACharacter ,public IInteractInterface
{
	GENERATED_BODY()


public:
	AHANEDANRPG3Character();
	//COMPONENTS
	
	//FUNCTIONS

	//Interfaces

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

	virtual void GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration, float DamageTickRate) override;
	// Character Actions

	//* This function  drawweapon if weaponvalid
	// will check weaponvalid and  bisweapononhand
	//*/
	virtual void DrawWeapon();

	//* This function putback weapon if weaponvalid
	//will check weaponvalid and  bisweapononhand and change bisweapononhand
	//*/
	virtual void PutBackWeapon();

	//* Tüm checkler yapıldı inputfonksiyonunda direk çağırılabilir */
	virtual void LightAttack (bool bWithWeaponComp);
	
	/**
	 * can cast check edildi
	 * @param bWithWeaponComp true ise advanced karakterdir
	 */
	virtual void CastSkill (bool bWithWeaponComp, int32 ArraySkillNumber);

	virtual void PerformGuarding();
	virtual void PerformExitGuarding();

	UFUNCTION(BlueprintCallable)
	virtual void PerformDie();
	
	//* hitreact ve animinstance p ler check edildi
	//
	//*/
	virtual void PlayHitReactMontage(const FName& SectionName);

	/** bLoop true ise hasarı yedikten sonra eğer karkater ölüres ölüm animine geçmeden yerde knockout loop montagenin devam etmesini sağlar */
	virtual void PlayKnockOutMontage(bool bLoop);

	virtual void PlayStunnedMontage();

	virtual void PlayDeathMontage();
	
	virtual void GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction=FName());
	
	//Initialize

	virtual void InitializeWeapons(const TSubclassOf<ABaseWeapon>&InFirstWeaponClass, const TSubclassOf<ABaseWeapon>& InSecondWeaponClass);
	
	//States

	/** Check can interact*/
	virtual bool CanPerformInteract() const;
	
	/** Check can ride*/
	virtual bool CanPerformRide() const;

	/** Check can equip*/
	virtual bool CanPerformEquipping() const;

	/** CanPerformAttack*/
	virtual bool CanPerformAttack() const;

	/** CanPerformCast*/
	virtual bool CanPerformCast() const;

	virtual bool CanPerfromDodge() const;

	virtual bool CanPerformGuard() const;
	
	/** Reset characteractionstate and combattype */
	virtual void ResetStates();

	// Movement

	virtual void SetMovementMode(EMovementModes NewMovementMode);
	void SetMovementModeToSprinting();
	void SetMovementModeToRunning();
	
	
	//VARIABLES

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float MaxWalkSpeed = 300;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float MaxRunSpeed = 500;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float MaxSprintSpeed = 700;
	
	//Items

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Items")
	bool bIsWeaponOnHand=false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Items")
	TSubclassOf<ABaseWeapon> FirstWeaponClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Items")
	TSubclassOf<ABaseWeapon> SecondWeaponClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Items")
	ABaseWeapon* MainWeapon;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Items")
	ABaseWeapon* FirstWeapon;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Items")
	ABaseWeapon* SecondWeapon;

	//Montages

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	TArray<UAnimMontage*>AttackMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	TArray<UAnimMontage*>SkillMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* HitReactionMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* KnockOutMontages;

	/** Knockout yediği hasarda ölürse bu kullanılır */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* KnockOutLoop;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* StunnedMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* GuardingMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	TArray<UAnimMontage*>DodgeMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	TArray<UAnimMontage*>EquippingMontages;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	TArray<UAnimMontage*>IdleMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Montages")
	UAnimMontage* DeadMontage;
	
	//States

	/** Karakterin current hp si 0 a düştüğü anda falseye setlenir */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="States")
	bool bIsAlive = true;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="States")
	EActionStates CharacterActionState=EActionStates::Eas_Unocuppied;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="States")
	ECombatType CombatType=ECombatType::Ect_None;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="States")
	EMovementModes MovementMode = EMovementModes::Emm_Walking;
	

	//Like Combat Component ----------------------------------------------------------------
	bool bLastUsedWeaponisSword;
	float MaxLightAttackCount=0;
	float LightAttackCount=0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float MaxHP=100;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float CurrentHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float HPRegenRate = 2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float HPRegenCoolDown = 3;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float MaxSP=100;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float CurrentSP;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float SPRegenRate = 2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float SPRegenCoolDown = 3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float MaxStamina=100;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float CurrentStamina;;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float DodgeStaminaCost = 15;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float SprintingStaminaCost = 5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float StaminaRegenCoolDown = 3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float StaminaRegenRate = 3;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
    float BuffedDamage = 0;
    
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
    bool bBuffedDamageActivated = false;

	virtual void SetCurrentStatValue(EStats Stat, float number);

	/** SetCurrentStatValueyi çağırmaktadır girilen değeri topluyor. */
	virtual void ChangeCurrentStatValue(EStats Stat,float value);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHpPercent() const ;
	float GetCurrentSPPercent() const ;
	float GetCurrentStaminaPercent() const ;

	/** HP regen rateden alır */
	void RegenHP();
	void ReduceHP();
	void HPActionFucntion();
	FTimerHandle RegenHpTimerHandle;
	
	/** SP regen rateden alır */
	void RegenSP();
	void SPActionFucntion();
	FTimerHandle RegenSPTimerHandle;
	
	/** Stamina regen rateden alır */
	void RegenStamina();

	/** SprintingStaminaCost rateden alır */
	void ReduceStamina();
	
	/** İnputta çağırılır. timer kullanarak regenstamina yı çağırır */
	void StartSprintingCost();

	/** İnputta end yada interupt yiyince çağırılır. timerdaki  regenstamina yı çağırmayı durdurur. */
	void EndSprintingCost();

	void StartSprinting();
	void EndSprinting();

	/** ÖNEMLİ. Her Stamina tüketen olay sonrası çağıralacak fonksiyondur. Sprinting hariç*/
	void StaminaActionFucntion();
	FTimerHandle RegenStaminaTimerHandle;
	
	
	void IncreaseLightAttackCountAndControl();
	virtual void EnableWeaponTrace();
	virtual void DisableWeaponTrace();

	//---------------------------------------------------------------------------------------------------

	//GAMEPLAY EFFECTS

	UPROPERTY(EditDefaultsOnly,Category="GameplayEffects")
	float FireGameplayEffectDamage = 3;

	UPROPERTY(EditDefaultsOnly,Category="GameplayEffects")
	float FireGameplayEffectTime = 8;

	UPROPERTY(EditDefaultsOnly,Category="GameplayEffects")
	UParticleSystemComponent* FireGamePlayEffectParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly,Category="GameplayEffects")
	UParticleSystem* FireGameplayEffectParticle;

	UPROPERTY(VisibleAnywhere,Category="GameplayEffects")
	bool bFireGEActivated = false;

	UPROPERTY()
	FTimerHandle FireGameplayEffectTimerHandle;

	UPROPERTY()
	FTimerHandle FireGameplayEffectEndTimerHandle;

	/** if(FireGamePlayEffectParticleSystemComponent && FireGameplayEffectParticle && GetMesh()) */
	UFUNCTION(BlueprintCallable)
	virtual void ApplyFireGamePlayEffect();

	/** if(FireGamePlayEffectParticleSystemComponent) */
	UFUNCTION(BlueprintCallable)
	virtual void DisableFireGamePlayEffect();

	UFUNCTION(BlueprintCallable)
	void DoFireGEDamage();

	
	//Skills
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ADamageActor* ActiveSkillDamageActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* ActiveSkillVFXComponent;
	
protected:
	virtual void BeginPlay() override ;
	//COMPONENTS
	
	//FUNCTIONS
	
	//VARIABLES
	
private:
	//COMPONENTS
	
	//FUNCTIONS
	
	//VARIABLES
	
	
};

