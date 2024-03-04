// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/EnemyCharacters/BasicEnemy.h"

#include "Components/ProgressBar.h"
#include "Components/TraceComponent.h"
#include "Controllers/BaseAIController.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidget.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidgetComponent.h"

ABasicEnemy::ABasicEnemy()
{
	MeshTraceComponent=CreateDefaultSubobject<UTraceComponent>(TEXT("MeshTraceComponent"));
	
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
}

void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	HealthBarWidget =Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
	HealthBarWidgetComponent->SetVisibility(false);

	BaseAIController = Cast<ABaseAIController>(Controller);
	if(BaseAIController)
	{
		BaseAIController->RunBehaviorTree(CharacterBehaviorTree);
		BaseAIController->SetAIState(C_EAIStates::EAS_Passive,BaseAIController->GetBlackboardComponent());
		BaseAIController->SetStartLocation();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("baseaicontroller not valid"));
	}
	
}

void ABasicEnemy::GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage,
                            AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction)
{
	Super::GetDamage(DamageType, DamageEffectType, Damage, DamageCauserActor, OutHitResult, Direction);
	if(!HealthBarWidgetComponent->IsVisible() && bIsAlive)
	{
		HealthBarWidgetComponent->SetVisibility(true);
	}
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
}

void ABasicEnemy::PerformDie()
{
	Super::PerformDie();
	HealthBarWidgetComponent->SetVisibility(false);
}

void ABasicEnemy::SetCurrentStatValue(EStats Stat, float number)
{
	Super::SetCurrentStatValue(Stat, number);
	if(Stat == EStats::Ess_HP)
	{
		UpdateHealthWidgetHealthPercent();
	}
}

void ABasicEnemy::UpdateHealthWidgetHealthPercent()
{
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
}






