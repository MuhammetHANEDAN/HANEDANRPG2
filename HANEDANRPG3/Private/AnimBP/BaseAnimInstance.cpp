// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/Public/AnimBP//BaseAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "Kismet/KismetMathLibrary.h"


void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	HANEDANRPG3Character=Cast<AHANEDANRPG3Character>(TryGetPawnOwner());
	if(HANEDANRPG3Character)
	{
		CharacterMovementComponent=HANEDANRPG3Character->GetCharacterMovement();
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(HANEDANRPG3Character && CharacterMovementComponent)
	{
		GroundSpeed=UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
		bIsFalling=CharacterMovementComponent->IsFalling();
		ABP_CharacterState=HANEDANRPG3Character->CharacterActionState;
		ABP_CombatType=HANEDANRPG3Character->CombatType;
		Direction=CalculateDirection(CharacterMovementComponent->Velocity,HANEDANRPG3Character->GetActorRotation());
	}		
}



