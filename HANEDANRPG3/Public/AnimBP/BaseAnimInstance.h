// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "BaseAnimInstance.generated.h"

class UCharacterMovementComponent;
class AHANEDANRPG3Character;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite)
	AHANEDANRPG3Character* HANEDANRPG3Character;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	bool bIsFalling;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	float Direction;

	//States

	UPROPERTY(BlueprintReadWrite,Category=States)
	EActionStates ABP_CharacterState;

	UPROPERTY(BlueprintReadWrite,Category=States)
	ECombatType ABP_CombatType;
};


