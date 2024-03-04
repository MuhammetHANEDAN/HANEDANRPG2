// Fill out your copyright notice in the Description page of Project Settings.


#include "Rideable/RideableDragon.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "HANEDANRPG3/PlayerCharacter.h"
#include "HANEDANRPG3/Items/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
//#include "HANEDANRPG3/Enums/DebugMacros.h"

// Sets default values
ARideableDragon::ARideableDragon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch=false;
	bUseControllerRotationYaw=false;
	
	
	DragonBoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("DragonBoxComponent"));
	SetRootComponent(DragonBoxComponent);

	DragonSkeletalMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DragonSkeletalMesh"));
	DragonSkeletalMeshComponent->SetupAttachment(GetRootComponent());

	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation=true;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation=false;

	SpreadCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SpreadCapsule"));
	SpreadCapsuleComponent->SetupAttachment(GetRootComponent());

	RiderExitSceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("Rider Exit Scene"));
	RiderExitSceneComponent->SetupAttachment(GetRootComponent());

	FloatingPawnMovementComponent=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementCompomemt"));

	Tags.Add("Rideable");
}

// Called when the game starts or when spawned
void ARideableDragon::BeginPlay()
{
	Super::BeginPlay();
	CrosshairWidget=CreateWidget<UUserWidget>(GetWorld(),CrosshairWidgetClass);
	SpreadCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ARideableDragon::OnSpreadCollisionBeginOverlap);
	SpreadCapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ARideableDragon::OnSPreadCollisionEndOverlap);
	const FAttachmentTransformRules TransformRules=FAttachmentTransformRules::SnapToTargetIncludingScale;
	SpreadCapsuleComponent->AttachToComponent(DragonSkeletalMeshComponent,TransformRules,FName("FlameStartSocket"));
	SpreadCapsuleComponent->SetRelativeRotation(FRotator(90,0,0));
}

// Called every frame
void ARideableDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsDragonBeingDriven())
	{
		GetDistanceToGround();
	}
}

// Called to bind functionality to input
void ARideableDragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ARideableDragon::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ARideableDragon::Look);

		//Flying
		EnhancedInputComponent->BindAction(FlyAction,ETriggerEvent::Triggered,this,&ARideableDragon::Fly);

		//Aiming
		EnhancedInputComponent->BindAction(AimingAction,ETriggerEvent::Started,this,&ARideableDragon::Aiming);
		EnhancedInputComponent->BindAction(AimingAction,ETriggerEvent::Canceled,this,&ARideableDragon::AimingOff_I);
		EnhancedInputComponent->BindAction(AimingAction,ETriggerEvent::Completed,this,&ARideableDragon::AimingOff_I);

		//FireBall
		EnhancedInputComponent->BindAction(FireBallAction,ETriggerEvent::Started,this,&ARideableDragon::Fireball);

		//SpreadFire 
		EnhancedInputComponent->BindAction(SpreadFireAction,ETriggerEvent::Started,this,&ARideableDragon::SpreadFire);

		//EPress
		EnhancedInputComponent->BindAction(EPressAction,ETriggerEvent::Started,this,&ARideableDragon::EKeyPressed);
	}

}

// Called when controller possessed this 
void ARideableDragon::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	PossessedController=NewController;
	DragonState=EDragon::Ed_BeingDriven;
	if(APlayerController* PossessedPlayerController =Cast<APlayerController>(PossessedController))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PossessedPlayerController->GetLocalPlayer()))
		{
			bool bHasContext=Subsystem->HasMappingContext(RemoveMappingContext);
			if(bHasContext)
			{
				Subsystem->RemoveMappingContext(RemoveMappingContext);
			}
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
	
}

void ARideableDragon::UnPossessed()
{
	Super::UnPossessed();
	APlayerController* PlayerController=GetWorld()->GetFirstPlayerController();
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		bool bHasContext=Subsystem->HasMappingContext(RemoveMappingContext);
		if(bHasContext)
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
		}
	}
}

void ARideableDragon::Interact(APlayerCharacter* PlayerCharacter )
{
	if(PlayerCharacter)
	{
		InteractedCharacter=PlayerCharacter;
		Mount();
	}
}

void ARideableDragon::GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult,
	EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration,
	float DamageTickRate)
{
	IInteractInterface::GetHit_Implementation(DamageCauserActor, OutHitResult, DamageType, DamageEffectType, Damage,
	                                          DamageDuration, DamageTickRate);
}


void ARideableDragon::Mount()
{
	if(InteractedCharacter && !bIsDragonBeingDriven() && !bIsFlying && InteractedCharacter->CanPerformRide())
	{
		InteractedCharacter->GetController()->UnPossess();
		InteractedCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractedCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractedCharacter->GetMesh()->SetVisibility(false);
		if(InteractedCharacter->MainWeapon)
		{
			InteractedCharacter->MainWeapon->GetWeaponMeshComponent()->SetVisibility(false);
			InteractedCharacter->MainWeapon->GetWeaponMeshComponent2()->SetVisibility(false);
			InteractedCharacter->SecondWeapon->GetWeaponMeshComponent()->SetVisibility(false);
			InteractedCharacter->SecondWeapon->GetWeaponMeshComponent2()->SetVisibility(false);
		}
		InteractedCharacter->PutBackWeapon();
		InteractedCharacter->ResetStates();
		bool bIsAttached=InteractedCharacter->AttachToComponent(DragonSkeletalMeshComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale,DragonAttachName);
		if(bIsAttached)
		{
			DragonState=EDragon::Ed_BeingDriven;
			//Player Character State Changes
			InteractedCharacter->CharacterActionState=EActionStates::Eas_Riding;
			InteractedCharacter->Tags.Add(FName("Riding"));
			InteractedCharacter->CombatType=ECombatType::Ect_None;
			UFunctionLibrary::GetPlayerController(GetWorld())->Possess(this);
		}
	}
}

void ARideableDragon::DisMount()
{
	if(InteractedCharacter && bIsDragonBeingDriven() && !bIsFlying )
	{
		GetController()->UnPossess();
		InteractedCharacter->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		UFunctionLibrary::GetPlayerController(GetWorld())->Possess(InteractedCharacter);
		InteractedCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractedCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractedCharacter->GetMesh()->SetVisibility(true);
		if(InteractedCharacter->MainWeapon)
		{
			InteractedCharacter->MainWeapon->GetWeaponMeshComponent()->SetVisibility(true);
			InteractedCharacter->MainWeapon->GetWeaponMeshComponent2()->SetVisibility(true);
			InteractedCharacter->SecondWeapon->GetWeaponMeshComponent()->SetVisibility(true);
			InteractedCharacter->SecondWeapon->GetWeaponMeshComponent2()->SetVisibility(true);
		}
		DragonState=EDragon::Ed_Unocuppied;
		InteractedCharacter->CharacterActionState=EActionStates::Eas_Unocuppied;
		InteractedCharacter->Tags.Remove(FName("Riding"));
		UFunctionLibrary::GetPlayerController(GetWorld())->SetControlRotation(FRotator(0,0,0));
		InteractedCharacter->SetActorLocation(RiderExitSceneComponent->GetComponentLocation());
	}
}

void ARideableDragon::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector=Value.Get<FVector2d>();

	if(PossessedController!=nullptr)
	{
		/*FVector ForwardVector = GetActorForwardVector();
		FVector RightVector=GetActorRightVector();
		AddMovementInput(ForwardVector,MovementVector.Y);
		AddMovementInput(RightVector,MovementVector.X);*/
		
		FVector ForwardVector=GetActorForwardVector();
		FVector RightVector=GetActorRightVector();
		FRotator ControlRotation=GetControlRotation();
		FRotator YawRotation=FRotator(0,ControlRotation.Yaw,0);

		if(!bIsFlying)
		{
			const FVector ForwardAxisVector=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightAxisVector=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			const FRotator RF =FRotator(0,ControlRotation.Yaw-90,0);
			if(!bIsDragonStraightPosition)
			{
				bUseControllerRotationYaw=false;
				bUseControllerRotationPitch=false;
				DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,0,0));
				bIsDragonStraightPosition=true;
			}
			
			AddMovementInput(ForwardAxisVector,MovementVector.Y);
			AddMovementInput(RightAxisVector,MovementVector.X);
			GroundMovement(MovementVector,RF);
			
		}
		if(bIsFlying)
		{
			bUseControllerRotationYaw=true;
			bUseControllerRotationPitch=true;
			bIsDragonStraightPosition=false;
			const FVector ActorForwardVector=GetActorForwardVector();
			const FRotator ActorRotation=GetActorRotation();
			DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,ActorRotation.Yaw-90,ActorRotation.Pitch*-1));
			
			AddMovementInput(ActorForwardVector,MovementVector.Y);
		}

		
	}
}

void ARideableDragon::Look(const FInputActionValue& Value)
{
	FVector2d LookAxisVector=Value.Get<FVector2d>();
	if(PossessedController != nullptr)
	{
		if(!bIsFlying)
		{
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
		if(bIsFlying)
		{
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
	
}

void ARideableDragon::Fly(const FInputActionValue& Value)
{
	float ScaleValue=Value.Get<float>();
	FRotator ControlRotation=GetControlRotation();
	FRotator YawRotation=FRotator(0,ControlRotation.Yaw,0);
	if(PossessedController!=nullptr)
	{
		const FVector UpAxisVector=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
		AddMovementInput(UpAxisVector,ScaleValue);
	}
	
}

void ARideableDragon::Aiming(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed && bIsFlying && UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity)==0)
	{
		if(CrosshairWidget)
		{
			CrosshairWidget->AddToViewport();
		}
		bIsDragonAiming=true;
		FollowCamera->SetRelativeLocation(FVector(710,365,1240));
		FollowCamera->SetRelativeRotation(FRotator(-30,0,0));
	}

}

void ARideableDragon::AimingOff_I(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Aimingoff cagırıldı"));
	AimingOff();
}

void ARideableDragon::AimingOff()
{
	if(CrosshairWidget)
	{
		CrosshairWidget->RemoveFromParent();
	}
	if(bIsDragonAiming)
	{
		bIsDragonAiming=false;
		FollowCamera->SetRelativeLocation(FVector(0,0,0));
		FollowCamera->SetRelativeRotation(FRotator(0,0,0));
	}
}

void ARideableDragon::EKeyPressed(const FInputActionValue& Value)
{
	bool bPressed =Value.Get<bool>();
	if(bPressed)
	{
		DisMount();
	}
}

void ARideableDragon::Fireball(const FInputActionValue& Value)
{
	bool bPressed =Value.Get<bool>();
	if(bPressed && bIsDragonAiming && FireballAnimMontage && !bIsDragonAttacking)
	{
		DragonSkeletalMeshComponent->GetAnimInstance()->Montage_Play(FireballAnimMontage);
	}
}

void ARideableDragon::SpreadFire(const FInputActionValue& Value)
{
	bool bPressed =Value.Get<bool>();
	if(bPressed && !bIsDragonAttacking && !bIsFlying && SpreadFireMontage)
	{
		DragonSkeletalMeshComponent->GetAnimInstance()->Montage_Play(SpreadFireMontage);
	}
}

bool ARideableDragon::bIsDragonBeingDriven()
{
	return DragonState != EDragon::Ed_Unocuppied;
}

void ARideableDragon::GetDistanceToGround()
{
	FVector StartLocation =GetActorLocation();
	FVector EndLocation= FVector(StartLocation.X,StartLocation.Y,StartLocation.Z-1000000);
	FHitResult HitResult;
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldStatic);
	FCollisionQueryParams QParams;
	QParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult,StartLocation,EndLocation,Params,QParams);
	if(bHit)
	{
		DragonHeight= GetActorLocation().Z-HitResult.ImpactPoint.Z;
		if(DragonHeight>=FlyingStartHeight)
		{
			bIsFlying=true;
		}
		else
		{
			bIsFlying=false;
		}
	}
}

void ARideableDragon::GroundMovement(const FVector2d& MovementVector, const FRotator& RF)
{
	if(MovementVector.Y==1 && MovementVector.X==0)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(RF);
		UE_LOG(LogTemp,Warning,TEXT(" öne gidiyor"));
	}
	if(MovementVector.Y && MovementVector.X)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw+45,0));
		UE_LOG(LogTemp,Warning,TEXT(" ön sağ "));
	}
	if(MovementVector.Y==1 && MovementVector.X==-1)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw-45,0));
		UE_LOG(LogTemp,Warning,TEXT(" ön sol"));
	}
	if(MovementVector.Y==-1 && MovementVector.X==0)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw-180,0));
		UE_LOG(LogTemp,Warning,TEXT(" arka"));
	}
	if(MovementVector.Y==-1 && MovementVector.X==1)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw+135,0));
		UE_LOG(LogTemp,Warning,TEXT(" arka sağ"));
	}
	if(MovementVector.Y==-1 && MovementVector.X==-1)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw-135,0));
		UE_LOG(LogTemp,Warning,TEXT(" arka sol"));
	}
	if(MovementVector.Y==0 && MovementVector.X==1)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw+90,0));
		UE_LOG(LogTemp,Warning,TEXT(" sağ"));
	}
	if(MovementVector.Y==0 && MovementVector.X==-1)
	{
		DragonSkeletalMeshComponent->SetWorldRotation(FRotator(0,RF.Yaw-90,0));
		UE_LOG(LogTemp,Warning,TEXT("  sol"));
	}
}

void ARideableDragon::OnSpreadCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("oVERLAPPED"));
	if(bSpreadFireActivated)
	{
		if(OtherActor->ActorHasTag(FName("Enemy")))
		{
			TargetActors.Add(OtherActor);
		}
	}
}

void ARideableDragon::OnSPreadCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("DİSVERLAPPED"));
	if(bSpreadFireActivated)
	{
		if(OtherActor->ActorHasTag(FName("Enemy")))
		{
			TargetActors.Remove(OtherActor);
		}
	}
}

void ARideableDragon::StartSpreadFireDamage()
{
	bSpreadFireActivated = true;
	SpreadFlameVFX=UGameplayStatics::SpawnEmitterAttached(SpreadFireVFXClass,DragonSkeletalMeshComponent,FName("FlameStartSocket"),FVector::ZeroVector
		,FRotator::ZeroRotator,FVector(5,5,5));
	GetWorld()->GetTimerManager().SetTimer(SpreadFireDamageTimerHandle,this,&ARideableDragon::DoSpreadDamageToTargetActors,0.1,true);
}

void ARideableDragon::DoSpreadDamageToTargetActors()
{
	if(TargetActors.Num()==0) return;
	for (AActor* CurrentActor : TargetActors)
	{
		IInteractInterface* HitableActor= Cast<IInteractInterface>(CurrentActor);
		if(HitableActor)
		{
			FHitResult HitResult;
			HitableActor->GetHit_Implementation(this,HitResult,EDamageTypes::Edt_BasicDamage,ESkillDamageEffectTypes::Esdet_Fire
				,SpreadFireDamage,0,0);
		}
	}
}

void ARideableDragon::EndSpreadFireDamage()
{
	bSpreadFireActivated = false;
	TargetActors.Empty();
	if(SpreadFlameVFX)
	{
		SpreadFlameVFX->DestroyComponent();
	}
	GetWorld()->GetTimerManager().ClearTimer(SpreadFireDamageTimerHandle);
}





