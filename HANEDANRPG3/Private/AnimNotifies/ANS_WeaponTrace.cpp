// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_WeaponTrace.h"

#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "HANEDANRPG3/Items/BaseWeapon.h"

void UANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(AHANEDANRPG3Character* Character=Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		switch (TraceType)
		{
		default:
			TraceComponent=Character->FindComponentByClass<UTraceComponent>();
			if(TraceComponent)
			{
				TraceComponent->MeshSocketStartName=StartSocketName;
				TraceComponent->MeshSocketEndName=EndSocketName;
				TraceComponent->bMeshSocketsTrace=true;
				TraceComponent->TraceRadius=Radius;
				TraceComponent->Damage=Damage;
				TraceComponent->EnableTrace();
			}
			break;
		case ETraceType::Ett_Weapon_SingleWeapon:
			TraceComponent =Character->MainWeapon->GetWeaponTraceComponent();
			if(TraceComponent)
			{
				TraceComponent->bSingleWeaponTrace=true;
				Character->EnableWeaponTrace();
			}
			break;
		case ETraceType::Ett_Weapon_DualWeapon:
			TraceComponent =Character->MainWeapon->GetWeaponTraceComponent();
			if(TraceComponent)
			{
				TraceComponent->bDualWeaponTrace=true;
				TraceComponent->bFirstWeapon=bFirstWeapon;
				Character->EnableWeaponTrace();
			}
			break;
		}
		
	}
}

void UANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(AHANEDANRPG3Character* Character=Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		switch (TraceType)
		{
		default:
			TraceComponent=Character->FindComponentByClass<UTraceComponent>();
			if(TraceComponent)
			{
				TraceComponent->DisableTrace();
			}
			break;
		case ETraceType::Ett_Weapon_SingleWeapon:
			Character->DisableWeaponTrace();
			break;
		case ETraceType::Ett_Weapon_DualWeapon:
			Character->DisableWeaponTrace();
			break;
		}
	}
}
