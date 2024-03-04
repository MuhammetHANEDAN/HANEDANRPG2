// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_SetCharacterMovementFlyingToWalking.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"

void UANS_SetCharacterMovementFlyingToWalking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(AHANEDANRPG3Character* Character=Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void UANS_SetCharacterMovementFlyingToWalking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(AHANEDANRPG3Character* Character=Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}
