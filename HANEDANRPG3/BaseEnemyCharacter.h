// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3Character.h"
#include "BaseEnemyCharacter.generated.h"

class UBehaviorTree;
class UHealthBarWidget;
class UHealthBarWidgetComponent;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API ABaseEnemyCharacter : public AHANEDANRPG3Character
{
	GENERATED_BODY()

public:
	ABaseEnemyCharacter();
protected:
	virtual void BeginPlay() override;
public:
	// AI ---------------

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn),Category="AI")
	UBehaviorTree* CharacterBehaviorTree;
	
	//-----------------

	/** TargetLockSystemden trgetlendiği anda True ve target bırakıldığı anda false ye setlenmeli */
	UPROPERTY(VisibleAnywhere)
	bool bOnTargeted = false;

	virtual void GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction) override;

	virtual void PerformDie() override;
	
};
