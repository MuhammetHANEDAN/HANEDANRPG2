// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_DragonSpreadFire.h"

#include "Rideable/RideableDragon.h"

void UANS_DragonSpreadFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(ARideableDragon* Dragon = Cast<ARideableDragon>(MeshComp->GetOwner()))
	{
		Dragon->StartSpreadFireDamage();
	}
}

void UANS_DragonSpreadFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(ARideableDragon* Dragon = Cast<ARideableDragon>(MeshComp->GetOwner()))
	{
		Dragon->EndSpreadFireDamage();
	}
}
