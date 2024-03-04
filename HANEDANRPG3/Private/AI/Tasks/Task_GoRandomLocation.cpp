// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Task_GoRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

UTask_GoRandomLocation::UTask_GoRandomLocation()
{
	NodeName=TEXT("Go Random Location");
}

EBTNodeResult::Type UTask_GoRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UNavigationSystemV1* Navigate = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation TargetLocation;
	
	Navigate->GetRandomReachablePointInRadius(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),Radius,TargetLocation);
	EPathFollowingRequestResult::Type Result =OwnerComp.GetAIOwner()->MoveToLocation(TargetLocation.Location,5);
	
	if(Result == EPathFollowingRequestResult::Type::RequestSuccessful) return EBTNodeResult::Succeeded;

	return EBTNodeResult::Succeeded;
}
