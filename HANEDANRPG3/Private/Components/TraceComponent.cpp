// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/Public/Components/TraceComponent.h"

#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "HANEDANRPG3/Interfaces/InteractInterface.h"
#include "HANEDANRPG3/Items/BaseWeapon.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	TargetObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle,this,&UTraceComponent::Initialize,0.1,false);
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if(bShouldTrace && bMeshSocketsTrace)
	{
		Tracing(GetMeshSocketLocation(MeshSocketStartName),GetMeshSocketLocation(MeshSocketEndName));
	}
	if(bShouldTrace && bSingleWeaponTrace)
	{
		Tracing(GetWeaponSocketLocation(MeshSocketStartName),GetWeaponSocketLocation(MeshSocketEndName));
	}
	if(bShouldTrace && bDualWeaponTrace)
	{
		if(bFirstWeapon)
		{
			Tracing(GetWeaponSocketLocation(MeshSocketStartName),GetWeaponSocketLocation(MeshSocketEndName));
		}
		else
		{
			Tracing(GetWeaponSocketLocation2(MeshSocketStartName),GetWeaponSocketLocation2(MeshSocketEndName));
		}
	}
	
}

void UTraceComponent::EnableTrace()
{
	bShouldTrace=true;
}

void UTraceComponent::DisableTrace()
{
	bShouldTrace=false;
	HittedActors.Empty();
	HitResults.Empty();
	bMeshSocketsTrace = false;
	bSingleWeaponTrace = false;
	bDualWeaponTrace = false;
}

void UTraceComponent::Tracing(const FVector& StartLocation, const FVector& EndLocation)
{
	if(bMeshSocketsTrace)
	{
		bool bHitted= UKismetSystemLibrary::SphereTraceMultiForObjects(WorldContextObject,StartLocation,EndLocation,
			TraceRadius,TargetObjectTypes,false,ActorsToIgnore,EDrawDebugTrace::None,HitResults,true);
		
		for (FHitResult& HitResult : HitResults)
		{
			AActor* L_HittedActor = HitResult.GetActor();
			if(HittedActors.Contains(L_HittedActor)) return;
			if(IInteractInterface* HitActor=Cast<IInteractInterface>(L_HittedActor))
			{
				HitActor->GetHit_Implementation(OwnerActor,HitResult,EDamageTypes::Edt_BasicDamage,ESkillDamageEffectTypes::Esdet_NoEffect, Damage, 0, 0);
			}
			HittedActors.AddUnique(L_HittedActor);
		}
	}
	else
	{
		bool bHitted= UKismetSystemLibrary::SphereTraceMultiForObjects(WorldContextObject,StartLocation,EndLocation,
			OwnerWeaponStruct.WeaponTraceRadius,TargetObjectTypes,false,ActorsToIgnore,EDrawDebugTrace::None,HitResults,true);
		

		for (FHitResult& HitResult : HitResults)
		{
			AActor* L_HittedActor = HitResult.GetActor();
			if(HittedActors.Contains(L_HittedActor)) return;
			if(IInteractInterface* HitActor=Cast<IInteractInterface>(L_HittedActor))
			{
				HitActor->GetHit_Implementation(OwnerActor,HitResult,EDamageTypes::Edt_BasicDamage,ESkillDamageEffectTypes::Esdet_NoEffect, OwnerWeaponStruct.BaseDamage+OwnerCharacter->BuffedDamage, 0, 0);
			}
			HittedActors.AddUnique(L_HittedActor);
		}
	}
}

FVector UTraceComponent::GetMeshSocketLocation(FName InSocketName) const
{
	if(OwnerCharacter)
	{
		return OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	}
	return FVector::ZeroVector;
}

FVector UTraceComponent::GetWeaponSocketLocation(FName InSocketName) const
{
	return OwnerWeapon->GetWeaponMeshComponent()->GetSocketLocation(InSocketName);
}

FVector UTraceComponent::GetWeaponSocketLocation2(FName InSocketName) const
{
	return OwnerWeapon->GetWeaponMeshComponent2()->GetSocketLocation(InSocketName);
}


void UTraceComponent::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("initialize girildi"));
	WorldContextObject=GetWorld();

	switch (TraceType)
	{
	default:
		OwnerActor=GetOwner();
		OwnerCharacter=Cast<AHANEDANRPG3Character>(OwnerActor);
		ActorsToIgnore.Add(OwnerActor);
		break;
	case ETraceType::Ett_Weapon_SingleWeapon:
		OwnerActor=GetOwner()->GetAttachParentActor();
		OwnerWeapon=Cast<ABaseWeapon>(GetOwner());
		OwnerWeaponStruct=OwnerWeapon->WeaponStruct;
		MeshSocketStartName=OwnerWeaponStruct.MeshStartSocketName;
		MeshSocketEndName=OwnerWeaponStruct.MeshEndSocketName;
		ActorsToIgnore.Add(GetOwner());
		ActorsToIgnore.Add(OwnerActor);
		OwnerCharacter=Cast<AHANEDANRPG3Character>(OwnerActor);
		if(OwnerCharacter == nullptr)
		{
			break;
		}
		break;
	case ETraceType::Ett_Weapon_DualWeapon:
		OwnerActor=GetOwner()->GetAttachParentActor();
		OwnerWeapon=Cast<ABaseWeapon>(GetOwner());
		OwnerWeaponStruct=OwnerWeapon->WeaponStruct;
		MeshSocketStartName=OwnerWeaponStruct.MeshStartSocketName;
		MeshSocketEndName=OwnerWeaponStruct.MeshEndSocketName;
		ActorsToIgnore.Add(GetOwner());
		ActorsToIgnore.Add(OwnerActor);
		OwnerCharacter=Cast<AHANEDANRPG3Character>(OwnerActor);
		if(OwnerCharacter == nullptr)
		{
			break;
		}
		break;
	}
}



