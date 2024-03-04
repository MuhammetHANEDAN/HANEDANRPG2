// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HANEDANRPG3/Public/Components/TraceComponent.h"
#include "ANS_WeaponTrace.generated.h"

/**
 * hanedanrpg3 characterler için dizayn edildi
 */
UCLASS()
class HANEDANRPG3_API UANS_WeaponTrace : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ETraceType TraceType;

	/** Tracetype meshsockettrace ise setlenilmesi gerekir. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName StartSocketName;

	/** Tracetype meshsockettrace ise setlenilmesi gerekir. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName EndSocketName;

	/** Tracetype meshsockettrace ise setlenilmesi gerekir. Setlenmezse 50 değeri baz alınır */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 50;

	/** Tracetype meshsockettrace ise setlenilmesi gerekir. Setlenmezse 10 değeri baz alınır */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage = 10;

	/** Eğer trace type dualweapon ise setlenilmesi gerekir tracce attırılacak silaha göre 1. mi 2. eldeki silahmı */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bFirstWeapon=false;
	
	UPROPERTY()
	UTraceComponent* TraceComponent;
};
