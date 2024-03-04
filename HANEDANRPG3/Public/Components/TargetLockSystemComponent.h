// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "TargetLockSystemComponent.generated.h"


class AHANEDANRPG3Character;
class USpringArmComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HANEDANRPG3_API UTargetLockSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetLockSystemComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	// VARIABLES---

	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	AController* OwnerController;

	UPROPERTY(VisibleAnywhere)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY()
	UCameraComponent* CharacterFollowCamera;

	UPROPERTY()
	USpringArmComponent* CharacterCameraBoom;

	UPROPERTY(VisibleAnywhere)
	AActor* TargetActor;

	bool bTargetLockedActivated = false;
	
	bool bIsSkilling = false;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryParams;

	UPROPERTY()
	TArray<AActor*>ActorsToIgnore;
	
	
	//INITIALİZE

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float TargetingDistance=500;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float SphereRadiusForSphereTrace=100;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float RinterSpeed=9;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float MaxTargetingDistance = 1000;

	/**
	 * setcamerapositionTotarget() fonksiyonunda karakterin spring arm componentini z ekseninde yükseltiyor ileride locklanılan targetin büyüklüğüne göre yükseklik ayarlanılabilir.
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float CameraBoomHeight=200;

	/**
	 * setcamerapositionTotarget() fonksiyonunda follow cameranın pitchini ayarlamakta ilerde locklanılan targetin büyüklüğüne göre dinamik bir şekilde, iyi bir görüş açısı için setlenilebilir
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Initialize)
	float CameraPitch=-15;
	
	//---------

	//FUNCTIONS

	void LockOn();
	
	void LockOff();
	
	AActor* FindTarget();
	void UpdateRotation(float DeltaTime);
	void SetRotationMode(bool bOrientToCamera);
	void SetCameraPositionToTargeting();
	void SetCameraPositionToNotTargeting();
	void SetMovementMode(EMovementModes MovementMode);
	float TargetDistance();
	bool TargetInDıstance();
		
};
