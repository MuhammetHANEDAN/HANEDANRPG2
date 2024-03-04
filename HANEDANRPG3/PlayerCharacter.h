// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3Character.h"
#include "InputActionValue.h"
#include "Structs/ItemStruct.h"
#include "PlayerCharacter.generated.h"

class UPlayerCharacterOverlayWidget;
class AMainHUD;
class ARideableDragon;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API APlayerCharacter : public AHANEDANRPG3Character
{
	GENERATED_BODY()
public:
	APlayerCharacter(); //Constructor
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UTargetLockSystemComponent* TargetLockSystemComponent;
	
	//FUNCTIONS
	
	//VARIABLES
	
	
	//INPUT

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Sprinting Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintingAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Camera Zoom Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraZoomAction;

	/** InteractInput Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** InteractInput Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DrawOrPutWeaponToBackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchWeaponAction;

	/** InteractInput Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LightAttackAction;

	/** Skill Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill5Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Skill6Action;

	/** Dodge Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SlideAction;

	/** TargetLockSystem Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_TargetLockOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_TargetLockOff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GuardingAction;
	
	
protected:
	//COMPONENTS
	
	//FUNCTIONS
	// To add mapping context
	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ACTIONS
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	void Sprinting(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for camerazoom input */
	void CameraZoom(const FInputActionValue& Value);

	/** Called for looking input */
	void Interact(const FInputActionValue& Value);

	/** Called for DrawWeapon input */
	void DrawWeaponOrPutback(const FInputActionValue& Value);
	void SwitchWeapon(const FInputActionValue& Value);

	void CastSkill(bool bWithWeaponComp, int32 ArraySkillNumber) override;
	//void CastSkillNew(bool bWithWeaponComp, int32 ArraySkillNumber);

	/** Called for LightAttack input */
	void LightAttack_I(const FInputActionValue& Value);

	void CastSkill1_I(const FInputActionValue& Value);
	void CastSkill2_I(const FInputActionValue& Value);
	void CastSkill3_I(const FInputActionValue& Value);
	void CastSkill4_I(const FInputActionValue& Value);
	void CastSkill5_I(const FInputActionValue& Value);
	void CastSkill6_I(const FInputActionValue& Value);

	/** Called for TargetLockSystem inputs */
	void LockON_I(const FInputActionValue& Value);
	void LockOff_I(const FInputActionValue& Value);

	/** Called For Dodge Input */
	void Dodge_I(const FInputActionValue& Value);
	void Slide_I(const FInputActionValue& Value);

	/** Called For Dodge Input */
	void Guarding_I(const FInputActionValue& Value);
	
	//VARIABLES

public:
	//COMPONENTS
	
	//FUNCTIONS

	//Interfaces

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	virtual void GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration, float DamageTickRate) override;
	//--------------------
	/** Possesed */
	virtual void PossessedBy(AController* NewController) override;
	/** UnPossesed */
	virtual void UnPossessed();

	//SOME FUNCTIONS
	/** Karakter roll atarken girilen son movement inputa göre karakteri döndürmek için gereken rotationu veren fonksiyondur.ANS de kullandık */
	FRotator GetDesiredRotation() const;

	//CHARACTER ACTIONS

	virtual void GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction) override;

	virtual void PerformGuarding() override;
	virtual void PerformExitGuarding() override;

	/** Sphere Trace for interactables  */
	AActor* InteractSphere();

	//Initializations
	virtual void InitializeWeapons(const TSubclassOf<ABaseWeapon>& InFirstWeaponClass, const TSubclassOf<ABaseWeapon>& InSecondWeaponClass) override;

	//STATES
	
	virtual bool CanPerformAttack() const override;
	
	virtual bool CanPerformCast() const override;

	virtual bool CanPerformGuard() const override;

	virtual void PerformDie() override;
	
	//RIDE

	// DODGE
	
	/** Dodge mekanik için kullanılan forwardorbackward ve rightorleft valuelerini 0 lıyor */
	void RefreshDirectionValues();
	
	FName CalculateDodgeDirection() const;
	
	/**
	 * @param bIsSlide true olursa karakter slide hareketi yapar false olursa rol hareketi yapar.
	 */
	void PerformDodge();
	void PerformSlide();
	

	//INPUTS

	/** To add mapping context if unposeeed = true default mapping context will be removed*/
	virtual void PossesMappingContext(bool bUnpossessed);
	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns TargetLockComponent suboject**/
	FORCEINLINE class UTargetLockSystemComponent* GetTargetLockSystemComponent() const { return TargetLockSystemComponent; }
	
	//VARIABLES

	// For Calculate Dodge Direction
	/** Using for dodge mechanics */
	float ForwardOrBackward;
	/** Using for dodge mechanics */
	float RightOrLeft;

	// STATS

	virtual void SetCurrentStatValue(EStats Stat, float number) override;

	// WIDGETS

	UPROPERTY(VisibleAnywhere)
	AMainHUD* MainHUD;

	UPROPERTY(VisibleAnywhere)
	UPlayerCharacterOverlayWidget* PlayerCharacterOverlayWidget;

	/** MainHUD ve PLayerCahracterOverlayWidget burada setlenmektedir. O widgetlarda bulunan progress barlarda buradan setlenmek
	 * tedir. 
	 */
	void InitializeMainHud(APlayerController* PlayerController);
	void SetPlayerCharacterOverlayWidgetHP(float Percent);
	void SetPlayerCharacterOverlayWidgetSP(float Percent);
	void SetPlayerCharacterOverlayWidgetStamina(float Percent);

	//RIDE

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Riding)
	ARideableDragon* RideableDragon;

	//Montages

	virtual void PlayKnockOutMontage(bool bLoop) override;
	
	//States
	
	

	//STRUCTS

	
};



