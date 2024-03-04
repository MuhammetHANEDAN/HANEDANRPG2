// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/EnemyCharacters/BossEnemy.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TraceComponent.h"
#include "Controllers/BaseAIController.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABossEnemy::ABossEnemy()
{
	MeshTraceComponent=CreateDefaultSubobject<UTraceComponent>(TEXT("MeshTraceComponent"));
}

void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
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
	if(!bIsClonedBoss)
	{
		HealthBarWidget=CreateWidget<UHealthBarWidget>(GetWorld(),HealthBarWidgetClass);
		if(HealthBarWidget)
		{
			HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
		}
	}
}

void ABossEnemy::GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage,
                           AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction)
{
	if(DamageCauserActor==this) return;
	if(bIsClonedBoss)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ClonedBossDestroyVFX,GetActorLocation());
		Destroy();
	}
	if(DamageEffectType==ESkillDamageEffectTypes::Esdet_Fire && !bFireGEActivated)
	{
		ApplyFireGamePlayEffect();
	}
	ChangeCurrentStatValue(EStats::Ess_HP,-Damage);
	if(GetCurrentHpPercent() <= 0.5 && !bCloned)
	{
		if(ClonedMontage == nullptr) return;
		bCloned = true;
		GetMesh()->GetAnimInstance()->Montage_Play(ClonedMontage);
	}
	HPActionFucntion();
	UE_LOG(LogTemp,Error,TEXT("damage alındı"));
	UE_LOG(LogTemp,Error,TEXT("current hp = %f"),CurrentHP);
	if(DamageType==EDamageTypes::Edt_HeavyDamage)
	{
		int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(1,4);
		if(RandomNumber == 1)
		{
			if(KnockOutMontages && bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
			{
				PlayKnockOutMontage(false);
			}
			if(KnockOutMontages && !bIsAlive && CharacterActionState != EActionStates::Eas_Knocked)
			{
				PlayKnockOutMontage(true);
			}
		}
	}
	// TODO
}

void ABossEnemy::SetCurrentStatValue(EStats Stat, float number)
{
	switch (Stat)
	{
	default:
		CurrentHP=number;
		UpdateHealthWidgetHealthPercent();
		if(GetCurrentHpPercent() <= 0.5 && !bCloned)
		{
			if(ClonedMontage == nullptr) return;
			bCloned = true;
			GetMesh()->GetAnimInstance()->Montage_Play(ClonedMontage);
		}
		if(CurrentHP == 0)
		{
			PerformDie();
		}
		break;
	case EStats::Ess_SP:
		CurrentSP=number;
		break;
	case EStats::Ess_Stamina:
		CurrentStamina=number;
		break;
	}
}

void ABossEnemy::UpdateHealthWidgetHealthPercent()
{
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
}

void ABossEnemy::PerformDie()
{
	Super::PerformDie();
	if(HealthBarWidget)
	{
		HealthBarWidget->RemoveFromParent();
	}
}
