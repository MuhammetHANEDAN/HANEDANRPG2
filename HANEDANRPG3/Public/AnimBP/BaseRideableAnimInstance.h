// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseRideableAnimInstance.generated.h"

enum class EDragon : uint8;
class ARideableDragon;
class UFloatingPawnMovement;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UBaseRideableAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite)
	ARideableDragon* Dragon;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Movement)
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Movement)
	bool bIsFlying;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=States)
	EDragon DragonState;
};
