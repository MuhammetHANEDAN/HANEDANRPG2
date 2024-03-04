// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_GoRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UTask_GoRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	
	UTask_GoRandomLocation();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 300;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
