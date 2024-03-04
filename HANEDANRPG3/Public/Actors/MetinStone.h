// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HANEDANRPG3/Interfaces/InteractInterface.h"
#include "MetinStone.generated.h"

class UHealthBarWidget;
class UHealthBarWidgetComponent;
class USphereComponent;

UCLASS()
class HANEDANRPG3_API AMetinStone : public AActor , public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetinStone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//INTERFACES

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

	virtual void GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration, float DamageTickRate) override;

	//COMPONENTS
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* MetinSphereComponent;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UStaticMeshComponent* MetinStaticMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Widgets")
	UHealthBarWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn3;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn4;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn5;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USceneComponent* Spawn6;

	//GENERALS
	
	void DestroyAction();

	//STATS
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="STATS")
	float MaxHP = 500;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="STATS")
	float CurrentHP;

	float GetCurrentHpPercent() const ;
	
	//VFX

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="VFX")
	UParticleSystem* DestroyExplosionVFX;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="VFX")
	UParticleSystem* SpawnVFXClass;

	//WİDGET
	
	UPROPERTY(VisibleAnywhere,Category="Widgets")
	UHealthBarWidget* HealthBarWidget;

	void UpdateWidgetHpPercent();

	//SPAWN

	void HandleSpawn();
	void ChoosePhase(int32 PhaseNumber);
	void SpawnPhase(TSubclassOf<AHANEDANRPG3Character> SpawnClass);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SPAWN")
	TSubclassOf<AHANEDANRPG3Character> Phase1Class;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SPAWN")
	TSubclassOf<AHANEDANRPG3Character> Phase2Class;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SPAWN")
	TSubclassOf<AHANEDANRPG3Character> Phase3Class;

	bool bPhase1Started = false;
	bool bPhase2Started = false;
	bool bPhase3Started = false;
	
};


