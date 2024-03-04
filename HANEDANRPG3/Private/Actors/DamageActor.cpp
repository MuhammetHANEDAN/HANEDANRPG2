// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamageActor.h"

#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "HANEDANRPG3/Interfaces/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ADamageActor::ADamageActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADamageActor::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter=Cast<AHANEDANRPG3Character>(Owner);
	switch (DamageActorType)
	{
	default:
		// ... 
		break;
	case EDamageActorType::Edat_AttachedDamageActor:
		if (Owner)
		{
			AttachToActor(Owner, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//FTimerHandle AttachedDamageTimerHandle
			// Tüm checkler doğruysa &ADamageActor::DoAttachedDamage bu fonksiyonla damageleri göndermeye başlıyoruz actor destroy yiyene kadar 
			GetOwner()->GetWorldTimerManager().SetTimer(GeneralTimerHandle, this, &ADamageActor::DoDamageToTargetActors, 0.1, true);
			if (OwnerCharacter && SkillVfx)
			{
				ActivateOwnerCharacterSkillVFX();
				OwnerCharacter->ActiveSkillVFXComponent=UGameplayStatics::SpawnEmitterAttached(SkillVfx,OwnerCharacter->GetMesh());
			}
		}
		break;
	case EDamageActorType::Edat_AttachedAuraActor:
		// ...
		break;
	case EDamageActorType::Edat_AttachedLocationDamageActor:
		//FTimerHandle AttachedDamageTimerHandle;
		GetOwner()->GetWorldTimerManager().SetTimer(GeneralTimerHandle, this, &ADamageActor::DoDamageToTargetActors, 0.1, true);
		break;
	case EDamageActorType::Edat_AreaDirectDamage:
		GetOwner()->GetWorldTimerManager().SetTimer(GeneralTimerHandle, this, &ADamageActor::DestroyActor,0.1f, false);
		break;
	case EDamageActorType::Edat_ProjectileDamageActor:
		GetOwner()->GetWorldTimerManager().SetTimer(GeneralTimerHandle, this, &ADamageActor::DestroyActor,ProjectileLifeTime, false);
		break;
	}
}


FVector ADamageActor::LineTraceAndGetLocation() const
{
	FHitResult HitResult;
	
	if(Owner == nullptr) return FVector::ZeroVector;
	const FVector OwnerLocation= Owner->GetActorLocation();
	const FVector A=Owner->GetActorForwardVector()*SpawnDistance;
	const FVector EndLocation = OwnerLocation+A;

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	bool bHitted = GetWorld()->LineTraceSingleByObjectType(HitResult,Owner->GetActorLocation(),EndLocation,QueryParams,Params);
	if(bHitted && HitResult.GetActor()->ActorHasTag(FName("Damageable")))
	{
		return HitResult.GetActor()->GetActorLocation();
	}
	return EndLocation;
}

AHANEDANRPG3Character* ADamageActor::GetOwnerCharacter() const 
{
	return OwnerCharacter;
}

FVector ADamageActor::GetTargetActorLocation(AActor* TargetActor) const
{
	if(TargetActor)
	{
		return TargetActor->GetActorLocation();
	}
	return FVector::ZeroVector;
}

FRotator ADamageActor::GetTargetActorRotation(AActor* TargetActor) const
{
	if(TargetActor)
	{
		return TargetActor->GetActorRotation();
	}
	return FRotator::ZeroRotator;
}

void ADamageActor::DoDamageToTargetActor(AActor* TargetActor,FHitResult InHitResult)
{
	if(TargetActor && TargetActor->ActorHasTag(FName("Damageable")))
	{
		IInteractInterface* Target = Cast<IInteractInterface>(TargetActor);
		Target->GetHit_Implementation(Owner,InHitResult,DamageType,DamageEffectType,Damage,DamageDuration,DamageTickRate);
	}
}


void ADamageActor::DoDamageToTargetActors()
{
	if(TargetActors.Num()==0) return;
	for (AActor* CurrentActor : TargetActors)
	{
		if(CurrentActor)
		{
			if(IInteractInterface* Target = Cast<IInteractInterface>(CurrentActor))
			{
				Target->GetHit_Implementation(OwnerCharacter,FHitResult(),DamageType,DamageEffectType,Damage,DamageDuration,DamageTickRate);
			}
		}
	}
}

void ADamageActor::ActivateOwnerCharacterSkillVFX()
{
	if(OwnerCharacter->ActiveSkillVFXComponent)
	{
		const bool bActive = OwnerCharacter->ActiveSkillVFXComponent->IsActive();
		if(!bActive)
		{
			OwnerCharacter->ActiveSkillVFXComponent->Activate();
		}
	}
}

void ADamageActor::DeactivateOwnerCharacterSkillVFX()
{
	if(OwnerCharacter)
	{
		if(OwnerCharacter->ActorHasTag(FName("Animal"))) return;
		if(OwnerCharacter->ActiveSkillVFXComponent)
		{
			const bool bActive = OwnerCharacter->ActiveSkillVFXComponent->IsActive();
			if(bActive)
			{
				OwnerCharacter->ActiveSkillVFXComponent->Deactivate();
			}
		}
	}
}

void ADamageActor::DestroyActor()
{
	DeactivateOwnerCharacterSkillVFX();
	Destroy();
}

void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

