// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Task_Focus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_Focus::UTask_Focus()
{
	
}


EBTNodeResult::Type UTask_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard == nullptr) return EBTNodeResult::Succeeded;
	if(bFocusOrClear)
	{
		if(GetTargetActor(Blackboard))
		{
			OwnerComp.GetAIOwner()->SetFocus(GetTargetActor(Blackboard));
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Succeeded;
	}
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
	return EBTNodeResult::Succeeded;
	
}

AActor* UTask_Focus::GetTargetActor(UBlackboardComponent* Blackboard) const 
{
	UObject* KeyValue = Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName);
	if(AActor* Actor = Cast<AActor>(KeyValue))
	{
		return Actor;
	}
	return nullptr;
}
