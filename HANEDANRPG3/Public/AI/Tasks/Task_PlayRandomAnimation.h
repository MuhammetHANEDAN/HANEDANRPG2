// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_PlayRandomAnimation.generated.h"

/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UTask_PlayRandomAnimation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	// Montage_Playden onsucces vs çekmek için farklı delegateler bağlamak gerektiğinden şimdilik iptal edildi bp den kullanıyoruz taski
	
	UTask_PlayRandomAnimation();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimMontage*> AnimMontages;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
