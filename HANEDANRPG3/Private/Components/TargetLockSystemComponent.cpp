// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetLockSystemComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HANEDANRPG3/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UTargetLockSystemComponent::UTargetLockSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetLockSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter=Cast<APlayerCharacter>(GetOwner());
	if(PlayerCharacter==nullptr) return;
	OwnerController=PlayerCharacter->GetController();
	if(OwnerController==nullptr) return;
	CharacterMovementComponent=PlayerCharacter->GetCharacterMovement();
	CharacterCameraBoom=PlayerCharacter->GetCameraBoom();
	CharacterFollowCamera=PlayerCharacter->GetFollowCamera();
	QueryParams.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ActorsToIgnore.Add(PlayerCharacter);
	
}

void UTargetLockSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!bIsSkilling && bTargetLockedActivated)
	{
		UpdateRotation(DeltaTime);
		if(!TargetInDıstance())
		{
			LockOff();
		}
	}
}

void UTargetLockSystemComponent::LockOn()
{
	if(AActor* L_HitActor=FindTarget())
	{
		TargetActor=L_HitActor;
		bTargetLockedActivated=true;
		SetRotationMode(true);
	}
	else
	{
		LockOff();
	}
}

void UTargetLockSystemComponent::LockOff()
{
	bTargetLockedActivated=false;
	TargetActor=nullptr;
	SetRotationMode(false);
}

AActor* UTargetLockSystemComponent::FindTarget()
{
	if(PlayerCharacter)
	{
		UE_LOG(LogTemp,Warning,TEXT("Player character validdir"))
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Player character valid değildir"))
		return nullptr;
	}
	FVector ActorLocation=PlayerCharacter->GetActorLocation();

	FVector FollowCameraForwardVector=CharacterFollowCamera->GetForwardVector();
	FVector FCameraMTargetDistance=FollowCameraForwardVector*TargetingDistance;
	
	FVector EndLocation=ActorLocation+FCameraMTargetDistance+FVector(0,0,100);
	
	FHitResult HitResult;
	
	bool bHitted=UKismetSystemLibrary::SphereTraceSingleForObjects(this,ActorLocation,EndLocation,SphereRadiusForSphereTrace,QueryParams,false,
		ActorsToIgnore,EDrawDebugTrace::None,HitResult,true);

	if(bHitted)
	{
		AActor* HitActor=HitResult.GetActor();
		if(HitActor->ActorHasTag("Enemy"))
		{
			return HitActor;
		}
	}
	return nullptr;
}

void UTargetLockSystemComponent::UpdateRotation(float DeltaTime)
{
	if(PlayerCharacter && TargetActor && OwnerController)
	{
		FRotator ActorRotation=PlayerCharacter->GetActorRotation();
		const FVector ActorLocation=PlayerCharacter->GetActorLocation();
		const FVector TargetActorLocation=TargetActor->GetActorLocation();

		FRotator FindTargetRotation=UKismetMathLibrary::FindLookAtRotation(ActorLocation,TargetActorLocation);
		
		//FRotator IntereptedTargetRotatoion=UKismetMathLibrary::RInterpTo(ActorRotation,FindTargetRotation,DeltaTime,RinterSpeed);
		FRotator TargetRotation=FRotator(0,FindTargetRotation.Yaw,0);

		OwnerController->SetControlRotation(TargetRotation);
	}
}

void UTargetLockSystemComponent::SetRotationMode(bool bOrientToCamera)
{
	if(PlayerCharacter)
	{
		if(bOrientToCamera)
		{
			PlayerCharacter->bUseControllerRotationYaw=false;
			CharacterMovementComponent->bUseControllerDesiredRotation=true;
			CharacterMovementComponent->bOrientRotationToMovement=false;
			SetCameraPositionToTargeting();
			PlayerCharacter->Tags.Add("Targeting");
			SetMovementMode(EMovementModes::Emm_Walking);
		}
		else
		{
			PlayerCharacter->bUseControllerRotationYaw=false;
			CharacterMovementComponent->bUseControllerDesiredRotation=false;
			CharacterMovementComponent->bOrientRotationToMovement=true;
			SetCameraPositionToNotTargeting();
			PlayerCharacter->Tags.Remove("Targeting");
			SetMovementMode(EMovementModes::Emm_Running);
		}
	}
}

void UTargetLockSystemComponent::SetCameraPositionToTargeting()
{
	if(PlayerCharacter)
	{
		FVector BoomRelativeLocation=CharacterCameraBoom->GetRelativeLocation();
		CharacterCameraBoom->SetRelativeLocation(FVector(BoomRelativeLocation.X,BoomRelativeLocation.Y,CameraBoomHeight));

		FRotator CameraRelativeRotation= CharacterFollowCamera->GetRelativeRotation();
		CharacterFollowCamera->SetRelativeRotation(FRotator(CameraPitch,CameraRelativeRotation.Yaw,CameraRelativeRotation.Roll));
	}
}

void UTargetLockSystemComponent::SetCameraPositionToNotTargeting()
{
	CharacterCameraBoom->SetRelativeLocation(FVector(0,0,0));
	CharacterFollowCamera->SetRelativeRotation(FRotator(0,0,0));
}

void UTargetLockSystemComponent::SetMovementMode(EMovementModes MovementMode)
{
	switch (MovementMode)
	{
	case EMovementModes::Emm_Sprinting:
		CharacterMovementComponent->MaxWalkSpeed=700;
		break;
	case EMovementModes::Emm_Running:
		CharacterMovementComponent->MaxWalkSpeed=500;
		break;
	case EMovementModes::Emm_Walking:
		CharacterMovementComponent->MaxWalkSpeed=300;
		break;
	default:
		CharacterMovementComponent->MaxWalkSpeed=500;
		break;
	}
}

float UTargetLockSystemComponent::TargetDistance()
{
	if(PlayerCharacter && TargetActor)
	{
		return PlayerCharacter->GetDistanceTo(TargetActor);
	}
	return 0;
}

bool UTargetLockSystemComponent::TargetInDıstance()
{
	return TargetDistance() <= MaxTargetingDistance;
}





