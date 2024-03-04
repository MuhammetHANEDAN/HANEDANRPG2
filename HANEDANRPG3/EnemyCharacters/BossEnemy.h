// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3/BaseEnemyCharacter.h"
#include "BossEnemy.generated.h"

class ABaseAIController;
class UTraceComponent;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API ABossEnemy : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ABossEnemy();
protected:
	virtual void BeginPlay() override;

private:

	// COMPONENTS

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Widgets",meta=(AllowPrivateAccess="true"))
	UTraceComponent* MeshTraceComponent;

public:

	UPROPERTY(VisibleAnywhere)
	ABaseAIController* BaseAIController;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UHealthBarWidget* HealthBarWidget;

	virtual void GetDamage(EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, AActor* DamageCauserActor, const FHitResult& OutHitResult, const FName& Direction) override;

	/** BossMage yüzde 20 canın altına düştüğünde BB ye gidilip Cloning statesine geçilecek ve bu değer trueye setlenilecek.
	 * sürekli bölünme olmasın diye */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	bool bCloned = false;

	/** Eğer Bu nesne bossun clonu olacaksa spawn edilirken bu boolun true ya setlenmesi lazımki getdamagede gelecek tek hitde yok olsunlar */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn),Category="AI")
	bool bIsClonedBoss = false;

	/** Cloned Bosslar tek hitte öldüğünde bu vfx ile destroylanacaklar */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	UParticleSystem* ClonedBossDestroyVFX;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	UAnimMontage* ClonedMontage;
	

	virtual void SetCurrentStatValue(EStats Stat, float number) override;
	
	/** Gerekli checkleri yapmaktadır */
	 virtual void UpdateHealthWidgetHealthPercent();
	 
	 virtual void PerformDie() override;

	//-----------------------
	
};
