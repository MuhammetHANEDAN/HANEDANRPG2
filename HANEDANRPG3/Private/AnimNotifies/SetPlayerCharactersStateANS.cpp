// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SetPlayerCharactersStateANS.h"

#include "HANEDANRPG3/HANEDANRPG3Character.h"


void USetPlayerCharactersStateANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(AHANEDANRPG3Character* PlayerCharacter = Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		PlayerCharacter->CharacterActionState=NewState;
		if(bForBoss)
		{
			
		}
		else if(NewState==EActionStates::Eas_Attacking || NewState==EActionStates::Eas_Casting )
		{
			PlayerCharacter->bUseControllerRotationYaw=true;
		}
	}
}

void USetPlayerCharactersStateANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(AHANEDANRPG3Character* PlayerCharacter = Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		PlayerCharacter->CharacterActionState=EndState;
		if(bForBoss)
		{
			
		}
		else if(NewState==EActionStates::Eas_Attacking || NewState==EActionStates::Eas_Casting)
		{
			PlayerCharacter->bUseControllerRotationYaw=false;
		}
	}
}
