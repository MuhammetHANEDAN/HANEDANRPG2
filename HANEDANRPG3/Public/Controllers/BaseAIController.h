// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

struct FAIStimulus;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
public:
	
	ABaseAIController();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UAIPerceptionComponent* AIPerceptionComponent;

	UFUNCTION()
	void OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus);

	void HandleSightSense(AActor* SensedActor, FAIStimulus Stimulus);

	void SetAIState(C_EAIStates State, UBlackboardComponent* ABlackboard, AActor* SensedActor = nullptr);

	void SetStartLocation();
	

	// Outstimulus = ... 
};
