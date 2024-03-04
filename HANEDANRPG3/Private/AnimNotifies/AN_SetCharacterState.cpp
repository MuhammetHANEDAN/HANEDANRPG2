// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SetCharacterState.h"

#include "HANEDANRPG3/PlayerCharacter.h"

void UAN_SetCharacterState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if(APlayerCharacter* PlayerCharacter= Cast<APlayerCharacter>(MeshComp->GetOwner()))
    {
        if(PlayerCharacter->CharacterActionState != NewState)
        {
            PlayerCharacter->CharacterActionState=NewState;
        }
    }
}
