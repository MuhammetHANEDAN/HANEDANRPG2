// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SpawnProjectileDamageActor.generated.h"

class ADamageActor;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UAN_SpawnProjectileDamageActor : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	TSubclassOf<ADamageActor> DamageActorClass;

	/** Default olarak actorun forwardından spawnlanır false yaparsan meshsocket name gir oradan spawn edilecek */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	bool bActorForwardOrMeshSocket;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FName SocketName;

	
};
