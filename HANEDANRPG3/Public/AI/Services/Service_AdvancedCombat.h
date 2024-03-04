// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "Service_AdvancedCombat.generated.h"

/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UService_AdvancedCombat : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	UService_AdvancedCombat();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ChasingRange = 1500;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float LongDistanceCombatRange = 1200;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CloseCombatRange = 600;

	void SetAIState(C_EAIStates State,UBlackboardComponent* Blackboard);

	AActor* GetTargetActor (UBlackboardComponent* Blackboard) const ;

	float GetDistanceToTargetActor(UBehaviorTreeComponent& OwnerComp) const ;
};
