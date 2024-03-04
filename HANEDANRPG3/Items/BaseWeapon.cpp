// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/Items/BaseWeapon.h"

#include "Components/TraceComponent.h"

ABaseWeapon::ABaseWeapon()
{
	WeaponStaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponStaticMeshComponent);
	//ilerde object type ı buradan setle şu an bp den setliyorsun overlapp all dynamiğe

	WeaponStaticMeshComponent2=CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh2");
	WeaponStaticMeshComponent2->SetupAttachment(WeaponStaticMeshComponent);

	WeaponTraceComponent=CreateDefaultSubobject<UTraceComponent>("WeaponTrace");

	
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::EquipToBack(USceneComponent* InSceneComponent)
{
	const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(DetachmentRules);
	const FAttachmentTransformRules TransformRules=FAttachmentTransformRules::SnapToTargetIncludingScale;
	WeaponStaticMeshComponent->AttachToComponent(InSceneComponent,TransformRules,WeaponStruct.AttachSocketName);
	if(bIsDualWeapon)
	{
		WeaponStaticMeshComponent2->AttachToComponent(InSceneComponent,TransformRules,WeaponStruct.AttachSocketName2);
	}
	
}

void ABaseWeapon::EquipToHand(USceneComponent* InSceneComponent)
{
	const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachFromActor(DetachmentRules);
	const FAttachmentTransformRules TransformRules=FAttachmentTransformRules::SnapToTargetIncludingScale;
	WeaponStaticMeshComponent->AttachToComponent(InSceneComponent,TransformRules,WeaponStruct.HandSocketName);
	if(bIsDualWeapon)
	{
		WeaponStaticMeshComponent2->AttachToComponent(InSceneComponent,TransformRules,WeaponStruct.HandSocketName2);
	}
}

AActor* ABaseWeapon::GetAttachedActor() const
{
	return GetAttachParentActor();
}







