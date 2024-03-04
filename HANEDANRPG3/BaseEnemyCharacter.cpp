// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

#include "Components/ProgressBar.h"
#include "HUD/Enemy/HealthBarWidget.h"
#include "HUD/Enemy/HealthBarWidgetComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	Tags.Add("Enemy");
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemyCharacter::GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage,
                                    AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction)
{
	if(DamageCauserActor->ActorHasTag(FName("Enemy"))) return;
	Super::GetDamage(DamageType,DamageEffectType, Damage, DamageCauserActor, OutHitResult, Direction);
}

void ABaseEnemyCharacter::PerformDie()
{
	Super::PerformDie();
}

