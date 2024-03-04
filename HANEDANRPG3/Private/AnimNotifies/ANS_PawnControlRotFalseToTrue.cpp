// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_PawnControlRotFalseToTrue.h"

void UANS_PawnControlRotFalseToTrue::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(APawn* OwnerPawn = Cast<APawn>(MeshComp->GetOwner()))
	{
		OwnerPawn->bUseControllerRotationYaw=false;
		UE_LOG(LogTemp,Warning,TEXT("ROTATİONYAW FALSE YAPILDI"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("ROTATİONYAW FALSE YAPILAMADI"));
	}
}

void UANS_PawnControlRotFalseToTrue::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(APawn* OwnerPawn = Cast<APawn>(MeshComp->GetOwner()))
	{
		OwnerPawn->bUseControllerRotationYaw=true;
	}
}
