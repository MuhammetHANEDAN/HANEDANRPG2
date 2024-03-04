// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "HANEDANRPG3/Interfaces/InteractInterface.h"
#include "RideableDragon.generated.h"

class UCapsuleComponent;
class APlayerCharacter;
class UInputAction;
class UInputMappingContext;
class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EDragon : uint8
{
	Ed_Unocuppied UMETA(DisplayName="Unocuppied"),
	Ed_BeingDriven UMETA(Displayname="BeingDriven")
};

UCLASS()
class HANEDANRPG3_API ARideableDragon : public APawn ,public IInteractInterface
{
	GENERATED_BODY()

private:
	//COMPONENTS

	//** Skeletal mesh component */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* DragonSkeletalMeshComponent;

	//** Root component */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UBoxComponent* DragonBoxComponent;

	//** CameraBoom */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	//** FollowCamera */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

	/** SpreadCollision using for spreadflame damage */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* SpreadCapsuleComponent;

	//** When rider exit */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	USceneComponent* RiderExitSceneComponent;

	//** FloatingPawnComponent */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	UFloatingPawnMovement* FloatingPawnMovementComponent;

	//FUNCTIONS
	

	//VARIABLES

	//INPUTS

	//** MappingContext /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputMappingContext* RemoveMappingContext;

	//** Move Input Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;

	//** Look Input Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;

	//** Fly Input Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* FlyAction;

	//** Aiming Input Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* AimingAction;

	//** Aiming Input Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* FireBallAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* SpreadFireAction;

	//** E Press Action /*
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* EPressAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//COMPONENTS
	
	//FUNCTIONS

	//Move Functions

	//** Move Function /*
	void Move(const FInputActionValue& Value);

	//** Look Function /*
	void Look(const FInputActionValue& Value);

	//** Fly Function /*
	void Fly(const FInputActionValue& Value);

	//** Aim Function /*
	void Aiming(const FInputActionValue& Value);
	void AimingOff_I(const FInputActionValue& Value);
	void AimingOff();

	//** EKey Pressed /*
	void EKeyPressed(const FInputActionValue& Value);

	//** Aim Function /*
	void Fireball(const FInputActionValue& Value);

	//** SpreadFire Function /*
	void SpreadFire(const FInputActionValue& Value);

	UFUNCTION()
	void OnSpreadCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnSPreadCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//VARIABLES	

public:
	// Sets default values for this pawn's properties
	ARideableDragon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	//COMPONENTS
	
	//FUNCTIONS

	//INTERFACES
	
	virtual void Interact(APlayerCharacter* PlayerCharacter ) override;
	virtual void GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration, float DamageTickRate) override;
	
	//SYSTEM
	//** Called when possessed /*
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed();

	//RIDING

	//* Mounting /*
	virtual void Mount();

	//* DisMounting /*
	virtual void DisMount();

	//State Checks

	//** Check dragon riding or uncocuppied /*
	bool bIsDragonBeingDriven();

	//Characters
	
	//** When the dragon being ride get distance to ground. And it will change the float DragonHeight variable and bool bisFlying variable /*
	void GetDistanceToGround();
	
	//VARIABLES

	//Widget

	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(VisibleDefaultsOnly,Category="Widgets")
	UUserWidget* CrosshairWidget;

	//** Possessed Controller Ref /*
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Controllers)
	AController* PossessedController;

	//MOVEMENT

	//** Dragon havadan yere inişe geçtiğinde ejderha düzeldimi/*
	UPROPERTY(VisibleAnywhere,Category=Movement)
	bool bIsDragonStraightPosition= true;

	//** This func. will move dragon when dragon riding at floor /*
	void GroundMovement(const FVector2d &MovementVector, const FRotator &RF);
	
	//Character
	
	//* DragonHeight */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Chacacter)
	float DragonHeight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Chacacter)
	float FlyingStartHeight = 40;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Chacacter)
	bool bIsFlying=false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Chacacter)
	bool bIsDragonAiming = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Chacacter)
	bool bIsDragonAttacking = false;


	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Chacacter)
	FName DragonAttachName;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Chacacter)
	APlayerCharacter* InteractedCharacter;

	// ATTACKS

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attacks)
	UAnimMontage* FireballAnimMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Attacks)
	UAnimMontage* SpreadFireMontage;

	// SPREAD FİRE 

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SpreadFire)
	float SpreadFireDamage = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SpreadFire)
	UParticleSystem* SpreadFireVFXClass;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=SpreadFire)
	bool bSpreadFireActivated = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=SpreadFire)
	TArray<AActor*> TargetActors;

	/** Attach edilecek vfx sonsuz oldugu için ans de sonda yok etmek için referansı buraya aktarıcaz */
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=SpreadFire)
	UParticleSystemComponent* SpreadFlameVFX;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=SpreadFire)
	FTimerHandle SpreadFireDamageTimerHandle;
	

	/** ANS de kullanılacak */
	void StartSpreadFireDamage();
	
	void DoSpreadDamageToTargetActors();

	/** ANS de kullanılacak */
	void EndSpreadFireDamage();

	//ENUMS

	//** State Enum /*
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Enums)
	EDragon DragonState=EDragon::Ed_Unocuppied;
	
	FORCEINLINE UFloatingPawnMovement* GetFloatingPawnMovementComponent() const {return FloatingPawnMovementComponent;}
	
};
