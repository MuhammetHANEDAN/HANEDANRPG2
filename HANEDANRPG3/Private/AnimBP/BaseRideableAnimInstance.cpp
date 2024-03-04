// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimBP/BaseRideableAnimInstance.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Rideable/RideableDragon.h"

void UBaseRideableAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Dragon=Cast<ARideableDragon>(TryGetPawnOwner());
	if(Dragon)
	{
		MovementComponent=Dragon->GetFloatingPawnMovementComponent();
	}
}

void UBaseRideableAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Dragon)
	{
		GroundSpeed=UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		bIsFlying=Dragon->bIsFlying;
		DragonState=Dragon->DragonState;
	}
}
