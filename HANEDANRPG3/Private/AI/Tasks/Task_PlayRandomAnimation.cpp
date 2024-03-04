// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Task_PlayRandomAnimation.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UTask_PlayRandomAnimation::UTask_PlayRandomAnimation()
{
	NodeName=TEXT("Play Random Animation");
}

EBTNodeResult::Type UTask_PlayRandomAnimation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if(ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if(AnimMontages.Num()>0)
		{
			int32 RandomNumber =UKismetMathLibrary::RandomIntegerInRange(0,AnimMontages.Num()-1);
			Character->GetMesh()->GetAnimInstance()->Montage_Play(AnimMontages[RandomNumber]);
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;
}
