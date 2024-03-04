// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "SetPlayerCharactersStateANS.generated.h"

/**
 * 
 */
UCLASS()
class HANEDANRPG3_API USetPlayerCharactersStateANS : public UAnimNotifyState
{
	GENERATED_BODY()
	//* Eger attacking statesine giriliyorsa usepawncontrolyaw true setlenip notifyda false ye setlenmektedir */
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnywhere)
	EActionStates NewState;

	UPROPERTY(EditAnywhere)
	EActionStates EndState;

	UPROPERTY(EditAnywhere)
	bool bForBoss = false;
	
};
