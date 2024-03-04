// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "HANEDANRPG3/EnemyCharacters/BossEnemy.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidget.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"


ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&ThisClass::OnTargetPerceptionUpdated_Delegate);
}


void ABaseAIController::OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
	case 0: // Görme
		HandleSightSense(Actor,Stimulus);
		break;
	case 1: // Duyma
		//SetHearSense(Actor,Stimulus);
		break;
	default:
		break;;
	}
}

void ABaseAIController::HandleSightSense(AActor* SensedActor, FAIStimulus Stimulus)
{
	bool bCanSee = Stimulus.WasSuccessfullySensed();
	if(GetBlackboardComponent() && SensedActor->ActorHasTag("Player"))
	{
		if(bCanSee)
		{
			if(AHANEDANRPG3Character* hanedanCharacter = Cast<AHANEDANRPG3Character>(GetPawn()))
			{
				UE_LOG(LogTemp,Warning,TEXT("hanedanrpg 3 character görüldü"));
			}

			SetAIState(C_EAIStates::EAS_Chasing,GetBlackboardComponent(),SensedActor);
			if(ABossEnemy* BossMage = Cast<ABossEnemy>(GetPawn()))
			{
				if(BossMage->bIsClonedBoss) return;
				if(BossMage->HealthBarWidget)
				{
					BossMage->HealthBarWidget->AddToViewport();
				}
			}
		}
		else
		{
			SetAIState(C_EAIStates::EAS_Passive,GetBlackboardComponent());
			if(ABossEnemy* BossMage = Cast<ABossEnemy>(GetPawn()))
			{
				if(BossMage->bIsClonedBoss) return;
				if(BossMage->HealthBarWidget)
				{
					if(BossMage->HealthBarWidget->IsInViewport())
					{
						BossMage->HealthBarWidget->RemoveFromParent();
					}
				}
			}
		}
	}
}

void ABaseAIController::SetAIState(C_EAIStates State, UBlackboardComponent* ABlackboard, AActor* SensedActor)
{
	switch (State)
	{
	default:
		// 
		break;
	case C_EAIStates::EAS_Passive:
		Blackboard->SetValueAsEnum(FName("AIState"),0);
		Blackboard->SetValueAsObject("TargetActor", nullptr);
		break;
	case C_EAIStates::EAS_CloseCombat:
		Blackboard->SetValueAsEnum(FName("AIState"),1);
		Blackboard->SetValueAsObject("TargetActor", SensedActor);
		break;
	case C_EAIStates::EAS_LongDistanceCombat:
		Blackboard->SetValueAsEnum(FName("AIState"),2);
		break;
	case C_EAIStates::EAS_Chasing:
		Blackboard->SetValueAsEnum(FName("AIState"),3);
		Blackboard->SetValueAsObject("TargetActor", SensedActor);
		break;
	case C_EAIStates::EAS_Waiting:
		Blackboard->SetValueAsEnum(FName("AIState"),4);
		break;
	}
}

void ABaseAIController::SetStartLocation()
{
	GetBlackboardComponent()->SetValueAsVector("StartLocation",GetPawn()->GetActorLocation());
}

