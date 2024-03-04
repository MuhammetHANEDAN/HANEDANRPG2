// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3/BaseEnemyCharacter.h"
#include "BasicEnemy.generated.h"

class ABaseAIController;
class UTraceComponent;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API ABasicEnemy : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ABasicEnemy();
protected:
	virtual void BeginPlay() override;

private:

	// COMPONENTS

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Widgets",meta=(AllowPrivateAccess="true"))
	UTraceComponent* MeshTraceComponent;

	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Widgets",meta=(AllowPrivateAccess="true"))
	UHealthBarWidgetComponent* HealthBarWidgetComponent;

public:

	UPROPERTY()
	UHealthBarWidget* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	ABaseAIController* BaseAIController;

	virtual void GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction) override;

	virtual void PerformDie() override;

	// WİDGETS -------------------

	virtual void SetCurrentStatValue(EStats Stat, float number) override;
	
	/** Gerekli checkleri yapmaktadır */
	virtual void UpdateHealthWidgetHealthPercent();

	//-----------------------
	
	FORCEINLINE UHealthBarWidgetComponent* GetHealthBarWidgetComponent() const { return HealthBarWidgetComponent;}
	FORCEINLINE void SetHealthBarWidgetComponent(UHealthBarWidgetComponent* NewHealthBarWidgetComponent) {HealthBarWidgetComponent = NewHealthBarWidgetComponent;}
};
