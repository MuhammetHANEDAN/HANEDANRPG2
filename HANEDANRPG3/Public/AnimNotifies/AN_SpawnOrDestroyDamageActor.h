// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SpawnOrDestroyDamageActor.generated.h"

class ADamageActor;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UAN_SpawnOrDestroyDamageActor : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	//* SpawnSelected DamageActor or Destroy activedamageactor if valid in hanedanrpg3 character */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	bool bSpawmOrDestroy;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	TSubclassOf<ADamageActor> DamageActorClass;
	
};
