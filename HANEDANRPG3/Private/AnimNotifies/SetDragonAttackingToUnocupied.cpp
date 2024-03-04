// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SetDragonAttackingToUnocupied.h"

#include "Rideable/RideableDragon.h"

void USetDragonAttackingToUnocupied::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(ARideableDragon* Dragon=Cast<ARideableDragon>(MeshComp->GetOwner()))
	{
		Dragon->bIsDragonAttacking=true;
	}
}

void USetDragonAttackingToUnocupied::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(ARideableDragon* Dragon=Cast<ARideableDragon>(MeshComp->GetOwner()))
	{
		Dragon->bIsDragonAttacking=false;
	}
}
