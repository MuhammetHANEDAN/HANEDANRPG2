// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TargetLockSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HUD/PlayerCharacterOverlayWidget.h"
#include "HUD/MainHUD/MainHUD.h"
#include "Interfaces/InteractInterface.h"
#include "Items/BaseWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength=400.f;
	CameraBoom->bUsePawnControlRotation=true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	TargetLockSystemComponent = CreateDefaultSubobject<UTargetLockSystemComponent>("TargetLockSystemComponent");

	Tags.Add("Player");
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		InitializeMainHud(PlayerController);
	}
	
	if(FirstWeaponClass && SecondWeaponClass)
	{
		InitializeWeapons(FirstWeaponClass,SecondWeaponClass);
	}
	
}


// Input


void APlayerCharacter::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::RefreshDirectionValues);

		EnhancedInputComponent->BindAction(SprintingAction,ETriggerEvent::Started,this, &APlayerCharacter::StartSprinting);
		EnhancedInputComponent->BindAction(SprintingAction,ETriggerEvent::Canceled,this, &APlayerCharacter::EndSprinting);
		EnhancedInputComponent->BindAction(SprintingAction,ETriggerEvent::Completed,this, &APlayerCharacter::EndSprinting);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//CameraZoom
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraZoom);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction,ETriggerEvent::Started,this,&APlayerCharacter::Interact);

		//DrawOrPutback a Weapon
		EnhancedInputComponent->BindAction(DrawOrPutWeaponToBackAction,ETriggerEvent::Started,this,&APlayerCharacter::DrawWeaponOrPutback);
		//Switch Weapon
		EnhancedInputComponent->BindAction(SwitchWeaponAction,ETriggerEvent::Started,this,&APlayerCharacter::SwitchWeapon);

		//LightAttack
		EnhancedInputComponent->BindAction(LightAttackAction,ETriggerEvent::Started,this,&APlayerCharacter::LightAttack_I);

		//Skills
		EnhancedInputComponent->BindAction(Skill1Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill1_I);
		EnhancedInputComponent->BindAction(Skill2Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill2_I);
		EnhancedInputComponent->BindAction(Skill3Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill3_I);
		EnhancedInputComponent->BindAction(Skill4Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill4_I);
		EnhancedInputComponent->BindAction(Skill5Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill5_I);
		EnhancedInputComponent->BindAction(Skill6Action,ETriggerEvent::Started,this,&APlayerCharacter::CastSkill6_I);

		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction,ETriggerEvent::Started,this,&APlayerCharacter::Dodge_I);
		EnhancedInputComponent->BindAction(SlideAction,ETriggerEvent::Started,this,&APlayerCharacter::Slide_I);

		//TargetLock
		EnhancedInputComponent->BindAction(IA_TargetLockOn,ETriggerEvent::Started,this,&APlayerCharacter::LockON_I);
		EnhancedInputComponent->BindAction(IA_TargetLockOff,ETriggerEvent::Started,this,&APlayerCharacter::LockOff_I);

		//Guarding
		EnhancedInputComponent->BindAction(GuardingAction,ETriggerEvent::Triggered,this,&APlayerCharacter::Guarding_I);
		EnhancedInputComponent->BindAction(GuardingAction,ETriggerEvent::Completed,this,&APlayerCharacter::PerformExitGuarding);
		EnhancedInputComponent->BindAction(GuardingAction,ETriggerEvent::Canceled,this,&APlayerCharacter::PerformExitGuarding);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	ForwardOrBackward=MovementVector.Y;
	RightOrLeft=MovementVector.X;

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !ActorHasTag(FName("Targeting")))
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::CameraZoom(const FInputActionValue& Value)
{
	float AxisValue = -1*Value.Get<float>();
	CameraBoom->TargetArmLength=UKismetMathLibrary::Clamp(CameraBoom->TargetArmLength+(50*AxisValue),600,1000);
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	bool Started = Value.Get<bool>();
	if(Started && CanPerformInteract())
	{
		AActor* InteractedActor = InteractSphere();
		if(IInteractInterface* InteractedActorInterface=Cast<IInteractInterface>(InteractedActor))
		{
			InteractedActorInterface->Interact(this);
		}
	}
}

void APlayerCharacter::DrawWeaponOrPutback(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed && MainWeapon && CanPerformEquipping())
	{
		if(!bIsWeaponOnHand)
		{
			if(MainWeapon->WeaponStruct.DrawAnimMontage)
			{
				GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.DrawAnimMontage);
			}
		}
		else
		{
			if(MainWeapon->WeaponStruct.DisArmAnimMontage)
			{
				GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.DisArmAnimMontage);
			}
		}
	}
}

void APlayerCharacter::SwitchWeapon(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		if(FirstWeapon && SecondWeapon)
		{
			PutBackWeapon();
			CombatType=ECombatType::Ect_None;
			if(MainWeapon->WeaponStruct.CombatType==ECombatType::Ect_GreatSword)
			{
				MainWeapon=SecondWeapon;
				if(MainWeapon->WeaponStruct.DrawAnimMontage)
				{
					GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.DrawAnimMontage);
					MaxLightAttackCount=MainWeapon->WeaponStruct.AttackMontages.Num();
					LightAttackCount=0;
				}
			}
			else
			{
				MainWeapon=FirstWeapon;
				if(MainWeapon->WeaponStruct.DrawAnimMontage)
				{
					GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.DrawAnimMontage);
					MaxLightAttackCount=MainWeapon->WeaponStruct.AttackMontages.Num();
					LightAttackCount=0;
				}
			}
		}
		
	}
}

void APlayerCharacter::CastSkill(bool bWithWeaponComp, int32 ArraySkillNumber)
{
	Super::CastSkill(bWithWeaponComp, ArraySkillNumber);
	if(CanPerformCast()==false) return;
	ChangeCurrentStatValue(EStats::Ess_SP,-MainWeapon->WeaponStruct.SkillManaCost);
	SPActionFucntion();
	if(MainWeapon)
	{
		TArray<UAnimMontage*> Montages = MainWeapon->WeaponStruct.SkillMontages;
		if(Montages.Num()==0)
		{
			return;
		}
		if(Montages[ArraySkillNumber])
		{
			GetMesh()->GetAnimInstance()->Montage_Play(Montages[ArraySkillNumber]);
		}
	}	
	
}

void APlayerCharacter::LightAttack_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed)
	{
		LightAttack(true);
	}
}

void APlayerCharacter::CastSkill1_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,0);
	}
}

void APlayerCharacter::CastSkill2_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,1);
	}
}

void APlayerCharacter::CastSkill3_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,2);
	}
}

void APlayerCharacter::CastSkill4_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,3);
	}
}

void APlayerCharacter::CastSkill5_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,4);
	}
}

void APlayerCharacter::CastSkill6_I(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if(bPressed)
	{
		CastSkill(true,5);
	}
}

void APlayerCharacter::LockON_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed && bIsWeaponOnHand)
	{
		TargetLockSystemComponent->LockOn();
	}
	
}

void APlayerCharacter::LockOff_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed)
	{
		TargetLockSystemComponent->LockOff();
	}
}

void APlayerCharacter::Dodge_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed)
	{
		switch (CombatType)
		{
		default:
			break;
		case ECombatType::Ect_GreatSword:
			PerformDodge();
			break;
		case ECombatType::Ect_DualSword:
			PerformDodge();
			break;
		}
	}
}

void APlayerCharacter::Slide_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed)
	{
		switch (CombatType)
		{
		default:
			break;
		case ECombatType::Ect_GreatSword:
			PerformSlide();
			break;
		case ECombatType::Ect_DualSword:
			PerformSlide();
			break;
		}
	}
}

void APlayerCharacter::Guarding_I(const FInputActionValue& Value)
{
	bool bPressed=Value.Get<bool>();
	if(bPressed && CharacterActionState!= EActionStates::Eas_Guarding)
	{
		PerformGuarding();
	}
}

void APlayerCharacter::PossesMappingContext(bool bUnpossessed)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			if(bUnpossessed)
			{
				Subsystem->RemoveMappingContext(DefaultMappingContext);
			}
		}
		
	}
}

void APlayerCharacter::SetCurrentStatValue(EStats Stat, float number)
{
	Super::SetCurrentStatValue(Stat, number);
	switch (Stat)
	{
	default:
		SetPlayerCharacterOverlayWidgetHP(GetCurrentHpPercent());
		break;
	case EStats::Ess_SP:
		SetPlayerCharacterOverlayWidgetSP(GetCurrentSPPercent());
		break;
	case EStats::Ess_Stamina:
		SetPlayerCharacterOverlayWidgetStamina(GetCurrentStaminaPercent());
		break;
	}
	
}

void APlayerCharacter::InitializeMainHud(APlayerController* PlayerController)
{
	if(PlayerController == nullptr) return;
	MainHUD =Cast<AMainHUD>(PlayerController->GetHUD());
	PlayerCharacterOverlayWidget = MainHUD->PlayerCharacterOverlayWidget;
	if(MainHUD && PlayerCharacterOverlayWidget)
	{
		MainHUD->PlayerCharacterOverlayWidget->HealthProgressBar->SetPercent(GetCurrentHpPercent());
		MainHUD->PlayerCharacterOverlayWidget->SPProgressBar->SetPercent(GetCurrentSPPercent());
		MainHUD->PlayerCharacterOverlayWidget->StaminaProgressBar->SetPercent(GetCurrentStaminaPercent());
	}
}

void APlayerCharacter::SetPlayerCharacterOverlayWidgetHP(float Percent)
{
	if(PlayerCharacterOverlayWidget)
	{
		PlayerCharacterOverlayWidget->HealthProgressBar->SetPercent(Percent);
	}
}

void APlayerCharacter::SetPlayerCharacterOverlayWidgetSP(float Percent)
{
	if(PlayerCharacterOverlayWidget)
	{
		PlayerCharacterOverlayWidget->SPProgressBar->SetPercent(Percent);
	}
}

void APlayerCharacter::SetPlayerCharacterOverlayWidgetStamina(float Percent)
{
	if(PlayerCharacterOverlayWidget)
	{
		PlayerCharacterOverlayWidget->StaminaProgressBar->SetPercent(Percent);
	}
}

void APlayerCharacter::PlayKnockOutMontage(bool bLoop)
{
	if(bLoop)
	{
		UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
		if(AnimInstance && MainWeapon->WeaponStruct.KnockOutLoopMontage)
		{
			AnimInstance->Montage_Play(MainWeapon->WeaponStruct.KnockOutLoopMontage);
		}
	}
	else
	{
		UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
		if(AnimInstance && MainWeapon->WeaponStruct.KnockOutMontage)
		{
			AnimInstance->Montage_Play(MainWeapon->WeaponStruct.KnockOutMontage);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("animinstance yada silahdaki montage invaliddir"))
		}
	}
}

//POSSES 

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	PossesMappingContext(false);
	
}

void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();
	PossesMappingContext(true);
}

FRotator APlayerCharacter::GetDesiredRotation() const
{
	if(GetCharacterMovement())
	{
		if(GetCharacterMovement()->GetLastInputVector() != FVector(0,0,0))
		{
			return UKismetMathLibrary::MakeRotFromX(GetLastMovementInputVector());
		}
		return GetActorRotation();
	}
	return FRotator::ZeroRotator;
}

void APlayerCharacter::GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage,
                                 AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction)
{
	if(DamageCauserActor==this) return;
	if(CharacterActionState==EActionStates::Eas_Dodging) return;
	ChangeCurrentStatValue(EStats::Ess_HP,-Damage);
	HPActionFucntion();
	UE_LOG(LogTemp,Error,TEXT("damage alındı"));
	UE_LOG(LogTemp,Error,TEXT("current hp = %f"),CurrentHP);
	if(DamageType==EDamageTypes::Edt_Damage && bIsAlive)
	{
		PlayHitReactMontage(Direction);
	}
	if(DamageEffectType==ESkillDamageEffectTypes::Esdet_Fire && !bFireGEActivated)
	{
		ApplyFireGamePlayEffect();
	}
	if(DamageType==EDamageTypes::Edt_HeavyDamage)
	{
		if(bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
		{
			PlayKnockOutMontage(false);
			UE_LOG(LogTemp,Warning,TEXT("knockout montage oynatılma komutu gönderildi"))
		}
		if(!bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
		{
			PlayKnockOutMontage(true);
		}
	}
}

void APlayerCharacter::PerformGuarding()
{
	if(CanPerformGuard() && MainWeapon && MainWeapon->WeaponStruct.GuardingMontage)
	{
		//Guarding montage başında kullanılacak bir AN ile state guardinge geçirilecek
		GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.GuardingMontage);
	}
}

void APlayerCharacter::PerformExitGuarding()
{
	if(CharacterActionState==EActionStates::Eas_Guarding && MainWeapon && MainWeapon->WeaponStruct.GuardingMontage)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.GuardingMontage);
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("DefenseExit"));
	}
}

//INTERFACES

void APlayerCharacter::Interact(APlayerCharacter* PlayerCharacter)
{
	Super::Interact(PlayerCharacter);
}

void APlayerCharacter::GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult,
	EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration,
	float DamageTickRate)
{
	Super::GetHit_Implementation(DamageCauserActor, OutHitResult, DamageType, DamageEffectType, Damage, DamageDuration,
	                             DamageTickRate);
}

//---------------------
AActor* APlayerCharacter::InteractSphere()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryParams;
	QueryParams.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingleForObjects(this,GetActorLocation(),GetActorLocation(),200,QueryParams,false,
		ActorsToIgnore,EDrawDebugTrace::None,HitResult,true);
	AActor* HitActor=HitResult.GetActor();
	if(HitActor)
	{
		return HitActor;
	}
	return nullptr;
}

void APlayerCharacter::InitializeWeapons(const TSubclassOf<ABaseWeapon>& InFirstWeaponClass,
	const TSubclassOf<ABaseWeapon>& InSecondWeaponClass)
{
	Super::InitializeWeapons(InFirstWeaponClass, InSecondWeaponClass);
}

bool APlayerCharacter::CanPerformAttack() const
{
	bool bCanAttack= Super::CanPerformAttack();
	bool bNotFalling=!GetMovementComponent()->IsFalling();
	return(bCanAttack && bNotFalling);
}

bool APlayerCharacter::CanPerformCast() const
{
	bool bCanCast=Super::CanPerformCast();
	bool bNotFalling=!GetMovementComponent()->IsFalling();
	return(bCanCast && bNotFalling);
}

bool APlayerCharacter::CanPerformGuard() const
{
	return Super::CanPerformGuard();
}

void APlayerCharacter::PerformDie()
{
	Super::PerformDie();
	if(FirstWeapon)
	{
		FirstWeapon->SetLifeSpan(5.f);
	}
	if(SecondWeapon)
	{
		SecondWeapon->SetLifeSpan(5.f);
	}
}

void APlayerCharacter::RefreshDirectionValues()
{
	ForwardOrBackward=0;
	RightOrLeft=0;
}

FName APlayerCharacter::CalculateDodgeDirection() const
{
	if(ForwardOrBackward==1 && RightOrLeft==0)
	{
		return "Forward";
	}
	if(ForwardOrBackward==1 && RightOrLeft==1)
	{
		return "Right";
	}
	if(ForwardOrBackward==1 && RightOrLeft==-1)
	{
		return"Left";
	}
	if(ForwardOrBackward==0 && RightOrLeft==1)
	{
		return "Right";
	}
	if(ForwardOrBackward==0 && RightOrLeft==-1)
	{
		return"Left";
	}
	if(ForwardOrBackward==-1 && RightOrLeft==0)
	{
		return "Backward";
	}
	if(ForwardOrBackward==-1 && RightOrLeft==1)
	{
		return "Right";
	}
	if(ForwardOrBackward==-1 && RightOrLeft==-1)
	{
		return "Left";
	}
	return "Forward";
}

void APlayerCharacter::PerformDodge()
{
	if(CanPerfromDodge()==false) return;
	UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(AnimInstance==nullptr) return;
	if(ActorHasTag("Targeting") || TargetLockSystemComponent->bIsSkilling==true)
	{
		UAnimMontage* RollMontage=MainWeapon->WeaponStruct.RollMontage;
		if(RollMontage)
		{
			if(MainWeapon && RollMontage)
			{
				AnimInstance->Montage_Play(RollMontage);
				AnimInstance->Montage_JumpToSection(CalculateDodgeDirection());
				ChangeCurrentStatValue(EStats::Ess_Stamina,-DodgeStaminaCost);
				StaminaActionFucntion();
			}
		}
	}
	else
	{
		UAnimMontage* RollForwardMontage=MainWeapon->WeaponStruct.RollForwardMontage;
		if(RollForwardMontage)
		{
			if(MainWeapon && RollForwardMontage)
			{
				AnimInstance->Montage_Play(RollForwardMontage);
				ChangeCurrentStatValue(EStats::Ess_Stamina,-DodgeStaminaCost);
				StaminaActionFucntion();
			}
		}
	}
}

void APlayerCharacter::PerformSlide()
{
	if(CanPerfromDodge()==false) return;
	UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(AnimInstance==nullptr) return;

	if(ActorHasTag("Targeting") || TargetLockSystemComponent->bIsSkilling==true)
	{
		UAnimMontage* SlideMontage=MainWeapon->WeaponStruct.SlideMontage;
		if(SlideMontage)
		{
			if(MainWeapon && SlideMontage)
			{
				AnimInstance->Montage_Play(SlideMontage);
				AnimInstance->Montage_JumpToSection(CalculateDodgeDirection());
			}
		}
	}
	else
	{
		UAnimMontage* RollForwardMontage=MainWeapon->WeaponStruct.RollForwardMontage;
		if(RollForwardMontage)
		{
			if(MainWeapon && RollForwardMontage)
			{
				AnimInstance->Montage_Play(RollForwardMontage);
			}
		}
	}
	
}






