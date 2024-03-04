// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_HandleSkillWhenTargeting.h"

#include "Components/TargetLockSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HANEDANRPG3/PlayerCharacter.h"

void UANS_HandleSkillWhenTargeting::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(APlayerCharacter* PlayerCharacter= Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		UCharacterMovementComponent* CharacterMovementComponent=PlayerCharacter->GetCharacterMovement();
		if(PlayerCharacter->ActorHasTag("Targeting"))
		{
			PlayerCharacter->Tags.Remove("Targeting");
			UTargetLockSystemComponent* TargetLock= PlayerCharacter->FindComponentByClass<UTargetLockSystemComponent>();
			if(TargetLock==nullptr) return;
			TargetLock->bIsSkilling=true;
			CharacterMovementComponent->bUseControllerDesiredRotation=false;
			CharacterMovementComponent->bOrientRotationToMovement=true;
		}
	}
}

void UANS_HandleSkillWhenTargeting::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(APlayerCharacter* PlayerCharacter= Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		UCharacterMovementComponent* CharacterMovementComponent=PlayerCharacter->GetCharacterMovement();
		UTargetLockSystemComponent* TargetLock= PlayerCharacter->FindComponentByClass<UTargetLockSystemComponent>();
		if(TargetLock->bTargetLockedActivated)
		{
			PlayerCharacter->Tags.Add("Targeting");
			TargetLock->bIsSkilling=false;
			CharacterMovementComponent->bUseControllerDesiredRotation=true;
			CharacterMovementComponent->bOrientRotationToMovement=false;
		}
	}
}
