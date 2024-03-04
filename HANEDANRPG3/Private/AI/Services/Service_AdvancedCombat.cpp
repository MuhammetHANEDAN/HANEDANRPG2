// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/Service_AdvancedCombat.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "Kismet/KismetMathLibrary.h"

UService_AdvancedCombat::UService_AdvancedCombat()
{
	NodeName=TEXT("Service Advanced Combat");
}

void UService_AdvancedCombat::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHANEDANRPG3Character* HanedanCharacter = Cast<AHANEDANRPG3Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(HanedanCharacter == nullptr) return;

	if(GetTargetActor(OwnerComp.GetBlackboardComponent()) && !GetTargetActor(OwnerComp.GetBlackboardComponent())->ActorHasTag(FName("Riding")))
	{
		if(HanedanCharacter->CharacterActionState!= EActionStates::Eas_Casting && HanedanCharacter->CharacterActionState!= EActionStates::Eas_Knocked)
		{
			if(GetDistanceToTargetActor(OwnerComp) > ChasingRange)
			{
				SetAIState(C_EAIStates::EAS_Chasing,OwnerComp.GetBlackboardComponent());
			}
			else
			{
				if(GetDistanceToTargetActor(OwnerComp) <= LongDistanceCombatRange)
				{
					if(GetDistanceToTargetActor(OwnerComp) <= CloseCombatRange)
					{
						SetAIState(C_EAIStates::EAS_CloseCombat,OwnerComp.GetBlackboardComponent());
					}
					else
					{
						SetAIState(C_EAIStates::EAS_LongDistanceCombat,OwnerComp.GetBlackboardComponent());
					}
				}
			}
		}
	}
	else
	{
		SetAIState(C_EAIStates::EAS_Passive,OwnerComp.GetBlackboardComponent());
	}
	
	
}

void UService_AdvancedCombat::SetAIState(C_EAIStates State, UBlackboardComponent* Blackboard)
{
	switch (State)
	{
	default:
		// 
		break;
	case C_EAIStates::EAS_Passive:
		Blackboard->SetValueAsEnum(FName("AIState"),0);
		break;
	case C_EAIStates::EAS_CloseCombat:
		Blackboard->SetValueAsEnum(FName("AIState"),1);
		break;
	case C_EAIStates::EAS_LongDistanceCombat:
		Blackboard->SetValueAsEnum(FName("AIState"),2);
		break;
	case C_EAIStates::EAS_Chasing:
		Blackboard->SetValueAsEnum(FName("AIState"),3);
		break;
	case C_EAIStates::EAS_Waiting:
		Blackboard->SetValueAsEnum(FName("AIState"),4);
		break;
	}
}

AActor* UService_AdvancedCombat::GetTargetActor(UBlackboardComponent* Blackboard) const
{
	UObject* Object =Blackboard->GetValueAsObject(FName("TargetActor"));
	if(AActor* Actor = Cast<AActor>(Object))
	{
		return Actor;
	}
	return nullptr;
}

float UService_AdvancedCombat::GetDistanceToTargetActor(UBehaviorTreeComponent& OwnerComp) const
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	FVector V1 = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	FVector V2= GetTargetActor(Blackboard)->GetActorLocation();
	return UKismetMathLibrary::Vector_Distance(V1,V2);
}

