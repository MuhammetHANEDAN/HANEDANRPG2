// Copyright Epic Games, Inc. All Rights Reserved.

#include "HANEDANRPG3Character.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TraceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Items/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"


//////////////////////////////////////////////////////////////////////////
// AHANEDANRPG3Character

AHANEDANRPG3Character::AHANEDANRPG3Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Tags
	Tags.Add(FName("Damageable"));

	CurrentHP=MaxHP;
	CurrentSP=MaxSP;
	CurrentStamina=MaxStamina;

}

void AHANEDANRPG3Character::BeginPlay()
{
	Super::BeginPlay();
}

void AHANEDANRPG3Character::Interact(APlayerCharacter* PlayerCharacter)
{
	
}

void AHANEDANRPG3Character::GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult,
	EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration,
	float DamageTickRate)
{
	if(DamageCauserActor==this)
	{
		UE_LOG(LogTemp,Warning,TEXT("Actor kendine hasar veremez returnlendi"));
		return;
	}
	if(DamageType!=EDamageTypes::Edt_BasicDamage)
	{
		FVector ForwardVector =GetActorForwardVector();
		FVector ImpactVector = (OutHitResult.ImpactPoint-GetActorLocation()).GetSafeNormal();
		const double ChosTheta =FVector::DotProduct(ForwardVector,ImpactVector);
		float Theta =FMath::Acos(ChosTheta);
		Theta = FMath::RadiansToDegrees(Theta);
		FVector CrossVector =FVector::CrossProduct(ForwardVector,ImpactVector);
		if(CrossVector.Z <0)
		{
			Theta *=-1.f;
		}
		FName Direction = FName("FromBack");

		if(Theta<45 && Theta >=-45)
		{
			Direction = FName("FromForward");
		}
		else if(Theta >= 45 && Theta<135)
		{
			Direction=FName("FromRight");
		}
		else if(Theta>=-135 && Theta<-45)
		{
			Direction=FName("FromLeft");
		}
		GetDamage(DamageType,DamageEffectType,Damage,DamageCauserActor,OutHitResult, Direction);
	}
	else
	{
		GetDamage(DamageType,DamageEffectType,Damage,DamageCauserActor, OutHitResult);
	}
}


void AHANEDANRPG3Character::SetCurrentStatValue(EStats Stat, float number)
{
	switch (Stat)
	{
	default:
		CurrentHP=number;
		if(CurrentHP == 0)
		{
			PerformDie();
		}
		break;
	case EStats::Ess_SP:
		CurrentSP=number;
		break;
	case EStats::Ess_Stamina:
		CurrentStamina=number;
		break;
	}
}

void AHANEDANRPG3Character::ChangeCurrentStatValue(EStats Stat, float value)
{
	float NewValue = 0;
	switch (Stat)
	{
	default:
		NewValue =  FMath::Clamp(CurrentHP+value,0,MaxHP);
		SetCurrentStatValue(Stat,NewValue);
		break;
	case EStats::Ess_SP:
		NewValue =  FMath::Clamp(CurrentSP+value,0,MaxSP);
		SetCurrentStatValue(Stat,NewValue);
		break;
	case EStats::Ess_Stamina:
		NewValue =  FMath::Clamp(CurrentStamina+value,0,MaxStamina);
		SetCurrentStatValue(Stat,NewValue);
		//Stamina için burada asla StaminActionFunctionu çağırma çünkü stamina reduce ve regen için aynı timerı kullanıyoruz.
		break;
	}
}

float AHANEDANRPG3Character::GetCurrentHpPercent() const
{
	return CurrentHP/MaxHP;
}

float AHANEDANRPG3Character::GetCurrentSPPercent() const 
{
	return CurrentSP/MaxSP;
}

float AHANEDANRPG3Character::GetCurrentStaminaPercent() const 
{
	return CurrentStamina/MaxStamina;
}


void AHANEDANRPG3Character::RegenHP()
{
	ChangeCurrentStatValue(EStats::Ess_HP,HPRegenRate);
	if(CurrentHP == MaxHP)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenHpTimerHandle);
	}
	if(!bIsAlive)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenHpTimerHandle);
	}
}

void AHANEDANRPG3Character::HPActionFucntion()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenHpTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenHpTimerHandle,this,&AHANEDANRPG3Character::RegenHP,0.1,true,HPRegenCoolDown);
}

void AHANEDANRPG3Character::RegenSP()
{
	ChangeCurrentStatValue(EStats::Ess_SP,SPRegenRate);
	if(CurrentSP == MaxSP)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenSPTimerHandle);
	}
	if(!bIsAlive)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenSPTimerHandle);
	}
}

void AHANEDANRPG3Character::SPActionFucntion()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenSPTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenSPTimerHandle,this,&AHANEDANRPG3Character::RegenSP,0.1,true,SPRegenCoolDown);
}

void AHANEDANRPG3Character::RegenStamina()
{
	ChangeCurrentStatValue(EStats::Ess_Stamina,StaminaRegenRate);
	if(CurrentStamina == MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	}
	if(!bIsAlive)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	}
}

void AHANEDANRPG3Character::ReduceStamina()
{
	ChangeCurrentStatValue(EStats::Ess_Stamina,-SprintingStaminaCost);
	if(CurrentStamina == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	}
}

void AHANEDANRPG3Character::StartSprintingCost()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenStaminaTimerHandle,this,&AHANEDANRPG3Character::ReduceStamina,0.1,true);
}

void AHANEDANRPG3Character::EndSprintingCost()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenStaminaTimerHandle,this,&AHANEDANRPG3Character::RegenStamina,0.1,true,3);
}

void AHANEDANRPG3Character::StartSprinting()
{
	if(ActorHasTag(FName("Targeting")))
	{
		return;
	}
	if(UKismetMathLibrary::VSizeXY(GetCharacterMovement()->Velocity)>0 && CurrentStamina>= 30)
	{
		SetMovementModeToSprinting();
		StartSprintingCost();
	}
}

void AHANEDANRPG3Character::EndSprinting()
{
	if(ActorHasTag(FName("Targeting")))
	{
		EndSprintingCost();
		return;
	}
	SetMovementModeToRunning();
	EndSprintingCost();
}

void AHANEDANRPG3Character::StaminaActionFucntion()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenStaminaTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenStaminaTimerHandle,this,&AHANEDANRPG3Character::RegenStamina,0.1,true,StaminaRegenCoolDown);
}


void AHANEDANRPG3Character::IncreaseLightAttackCountAndControl()
{
	LightAttackCount++;
	if(LightAttackCount==MaxLightAttackCount)
	{
		LightAttackCount=0;
	}
}


void AHANEDANRPG3Character::ApplyFireGamePlayEffect()
{
	if(bFireGEActivated) return;
	if(FireGameplayEffectParticle && GetMesh())
	{
		FireGamePlayEffectParticleSystemComponent=UGameplayStatics::SpawnEmitterAttached(FireGameplayEffectParticle,GetMesh(),FName("RootSocket"),FVector::ZeroVector,FRotator::ZeroRotator,
			FVector(4,4,4));
		bFireGEActivated=true;
		GetWorld()->GetTimerManager().SetTimer(FireGameplayEffectTimerHandle,this,&AHANEDANRPG3Character::DoFireGEDamage,0.1,true);
		GetWorld()->GetTimerManager().SetTimer(FireGameplayEffectEndTimerHandle,this,&AHANEDANRPG3Character::DisableFireGamePlayEffect,FireGameplayEffectTime,false);
	}
	if(FireGamePlayEffectParticleSystemComponent)
	{
		if(!FireGamePlayEffectParticleSystemComponent->IsActive())
		{
			FireGamePlayEffectParticleSystemComponent->Activate();
		}
	}
}

void AHANEDANRPG3Character::DisableFireGamePlayEffect()
{
	if(FireGamePlayEffectParticleSystemComponent)
	{
		if(FireGamePlayEffectParticleSystemComponent->IsActive())
		{
			FireGamePlayEffectParticleSystemComponent->Deactivate();
			bFireGEActivated=false;
		}
	}
	GetWorld()->GetTimerManager().ClearTimer(FireGameplayEffectTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(FireGameplayEffectEndTimerHandle);
}

void AHANEDANRPG3Character::DoFireGEDamage()
{
	ChangeCurrentStatValue(EStats::Ess_HP,-FireGameplayEffectDamage);
	if(CurrentHP == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireGameplayEffectTimerHandle);
	}
}


//INTERFACES



// CharacterActions

void AHANEDANRPG3Character::GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage,
                                      AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction)
{
	if(DamageCauserActor==this) return;
	if(!bIsAlive) return;
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
		if(KnockOutMontages && bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
		{
			PlayKnockOutMontage(false);
		}
		if(KnockOutMontages && !bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
		{
			PlayKnockOutMontage(true);
		}
	}
}

void AHANEDANRPG3Character::DrawWeapon()
{
	if(MainWeapon && !bIsWeaponOnHand)
	{
		MainWeapon->EquipToHand(GetMesh());
		bIsWeaponOnHand=true;
	}
}

void AHANEDANRPG3Character::PutBackWeapon()
{
	if(MainWeapon && bIsWeaponOnHand)
	{
		MainWeapon->EquipToBack(GetMesh());
		bIsWeaponOnHand=false;
	}
}

void AHANEDANRPG3Character::LightAttack(bool bWithWeaponComp) 
{
	if(CanPerformAttack()==false) return;
	if(MaxLightAttackCount==0)
	{
		UE_LOG(LogTemp,Warning,TEXT("max light attack count = 0 hanedanrpg3cpp 146"));
		return;
	}
	if(bWithWeaponComp && MainWeapon->WeaponStruct.AttackMontages[LightAttackCount])
	{
		GetMesh()->GetAnimInstance()->Montage_Play(MainWeapon->WeaponStruct.AttackMontages[LightAttackCount]);
		IncreaseLightAttackCountAndControl();
	}
}

void AHANEDANRPG3Character::CastSkill(bool bWithWeaponComp, int32 ArraySkillNumber)
{
	if(CanPerformCast()==false) return;
}

void AHANEDANRPG3Character::PerformGuarding()
{
	if(CanPerformGuard()==false)
	{
		return;
	}
}

void AHANEDANRPG3Character::PerformExitGuarding()
{
	
}

void AHANEDANRPG3Character::PerformDie()
{
	UE_LOG(LogTemp,Warning,TEXT("Karakter öldü"));
	bIsAlive=false;
	if(AController* CharacterController =GetController())
	{
		CharacterController->UnPossess();
	}
	if(AAIController* AController = Cast<AAIController>(GetController()))
	{
		AController->UnPossess();
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5);
	if(CharacterActionState == EActionStates::Eas_Knocked)
	{
		return;
	}
	PlayDeathMontage();
}

void AHANEDANRPG3Character::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(AnimInstance && HitReactionMontages)
	{
		AnimInstance->Montage_Play(HitReactionMontages);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void AHANEDANRPG3Character::PlayKnockOutMontage(bool bLoop)
{
	if(bLoop)
	{
		UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
		if(AnimInstance && KnockOutLoop)
		{
			AnimInstance->Montage_Play(KnockOutLoop);
		}
	}
	else
	{
		UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
		if(AnimInstance && KnockOutMontages)
		{
			AnimInstance->Montage_Play(KnockOutMontages);
		}
	}
}

void AHANEDANRPG3Character::PlayStunnedMontage()
{
	UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(AnimInstance && StunnedMontage)
	{
		AnimInstance->Montage_Play(StunnedMontage);
	}
}

void AHANEDANRPG3Character::PlayDeathMontage()
{
	UAnimInstance* AnimInstance=GetMesh()->GetAnimInstance();
	if(AnimInstance && DeadMontage)
	{
		AnimInstance->Montage_Play(DeadMontage);
	}
}

void AHANEDANRPG3Character::EnableWeaponTrace()
{
	if(MainWeapon)
	{
		MainWeapon->GetWeaponTraceComponent()->EnableTrace();
		UE_LOG(LogTemp,Warning,TEXT("weapon trace enabled"));
	}
}

void AHANEDANRPG3Character::DisableWeaponTrace()
{
	if(MainWeapon)
	{
		MainWeapon->GetWeaponTraceComponent()->DisableTrace();
	}
}

//ITEMS
void AHANEDANRPG3Character::InitializeWeapons(const TSubclassOf<ABaseWeapon>& InFirstWeaponClass, const TSubclassOf<ABaseWeapon>& InSecondWeaponClass)
{
	if(FirstWeaponClass && CombatType==ECombatType::Ect_None && SecondWeaponClass)
	{
		ABaseWeapon* Weapon1=Cast<ABaseWeapon>(GetWorld()->SpawnActor(FirstWeaponClass));
		ABaseWeapon* Weapon2=Cast<ABaseWeapon>(GetWorld()->SpawnActor(SecondWeaponClass));
		if(Weapon1)
		{
			FirstWeapon=Weapon1;
			MainWeapon=Weapon1;
			MainWeapon->EquipToBack(GetMesh());
			bIsWeaponOnHand=false;
		}
		if(Weapon2)
		{
			SecondWeapon=Weapon2;
			Weapon2->EquipToBack(GetMesh());
		}
		MaxLightAttackCount=MainWeapon->WeaponStruct.AttackMontages.Num();
	}
	
	
}

//STATE CHECKS

bool AHANEDANRPG3Character::CanPerformInteract() const
{
	bool bCanPenform=(CharacterActionState!=EActionStates::Eas_Attacking &&
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Guarding &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CharacterActionState!=EActionStates::Eas_Riding);
	return bCanPenform;
}

bool AHANEDANRPG3Character::CanPerformRide() const 
{
	bool bCanPenform=(CharacterActionState!=EActionStates::Eas_Attacking &&
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Guarding &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CharacterActionState!=EActionStates::Eas_Riding);
	return bCanPenform;
	
}

bool AHANEDANRPG3Character::CanPerformEquipping() const
{
	bool bCanPenform=(CharacterActionState!=EActionStates::Eas_Attacking &&
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Guarding &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CharacterActionState!=EActionStates::Eas_Riding);
	return bCanPenform;
}

bool AHANEDANRPG3Character::CanPerformAttack() const
{
	bool bCanPenform=(CharacterActionState!=EActionStates::Eas_Attacking &&
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Riding &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CurrentStamina >= MainWeapon->WeaponStruct.NormalAttackStaminaCost &&
		CombatType!=ECombatType::Ect_None &&
		bIsWeaponOnHand==true);
	return bCanPenform;
}

bool AHANEDANRPG3Character::CanPerformCast() const
{
	if(MainWeapon)
	{
		bool bCanPenform=(
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Riding &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CurrentSP >= MainWeapon->WeaponStruct.SkillManaCost &&
		CombatType!=ECombatType::Ect_None &&
		bIsWeaponOnHand==true);
		return bCanPenform;
	}
	return false;
}

bool AHANEDANRPG3Character::CanPerfromDodge() const
{
	bool bNotFalling=!GetMovementComponent()->IsFalling();
	bool bCanPenform=(
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Riding &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CurrentStamina >= DodgeStaminaCost &&
		CombatType!=ECombatType::Ect_None);
	return (bCanPenform && bNotFalling);
}

bool AHANEDANRPG3Character::CanPerformGuard() const
{
	bool bNotFalling=!GetMovementComponent()->IsFalling();
	bool bCanPenform=(
		CharacterActionState!=EActionStates::Eas_Casting &&
		CharacterActionState!=EActionStates::Eas_Dead &&
		CharacterActionState!=EActionStates::Eas_Guarding &&
		CharacterActionState!=EActionStates::Eas_Dodging &&
		CharacterActionState!=EActionStates::Eas_Equipping &&
		CharacterActionState!=EActionStates::Eas_JumpingOrFalling &&
		CharacterActionState!=EActionStates::Eas_Riding &&
		CharacterActionState!=EActionStates::Eas_Knocked &&
		CombatType!=ECombatType::Ect_None &&
		bIsWeaponOnHand==true);
	return bCanPenform && bNotFalling;
}

void AHANEDANRPG3Character::ResetStates()
{
	CharacterActionState=EActionStates::Eas_Unocuppied;
	CombatType=ECombatType::Ect_None;
}

void AHANEDANRPG3Character::SetMovementMode(EMovementModes NewMovementMode)
{
	if(UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		
		if(NewMovementMode != MovementMode)
		{
			MovementMode=NewMovementMode;
			switch (MovementMode)
			{
			default:
				MovementComponent->MaxWalkSpeed=MaxSprintSpeed;
				break;
			case EMovementModes::Emm_Running:
				MovementComponent->MaxWalkSpeed=MaxRunSpeed;
				break;
			case EMovementModes::Emm_Walking:
				MovementComponent->MaxWalkSpeed=MaxWalkSpeed;
				break;
			}
		}
	}
}

void AHANEDANRPG3Character::SetMovementModeToSprinting()
{
	SetMovementMode(EMovementModes::Emm_Sprinting);
	
}

void AHANEDANRPG3Character::SetMovementModeToRunning()
{
	SetMovementMode(EMovementModes::Emm_Running);
}


//////////////////////////////////////////////////////////////////////////





