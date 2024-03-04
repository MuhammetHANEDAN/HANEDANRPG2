// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_RotateToLastMoveWhenRolling.h"

#include "HANEDANRPG3/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_RotateToLastMoveWhenRolling::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                   float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	PlayerCharacter=Cast<APlayerCharacter>(MeshComp->GetOwner());
}

void UANS_RotateToLastMoveWhenRolling::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                  float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if(PlayerCharacter)
	{
		FRotator CurrentRotation=PlayerCharacter->GetActorRotation();
		FRotator TargetRotation=PlayerCharacter->GetDesiredRotation();
		FRotator EndRotation=UKismetMathLibrary::RInterpTo_Constant(CurrentRotation,TargetRotation,FrameDeltaTime,720);
		PlayerCharacter->SetActorRotation(EndRotation);
	}
}
