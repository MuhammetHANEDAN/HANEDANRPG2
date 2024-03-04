// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "AN_SetCharacterState.generated.h"

/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UAN_SetCharacterState : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EActionStates NewState;
};
