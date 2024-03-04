// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MetinStone.h"

#include "Components/ProgressBar.h"
#include "Components/SphereComponent.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidget.h"
#include "HANEDANRPG3/HUD/Enemy/HealthBarWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMetinStone::AMetinStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Damageable"));
	Tags.Add(FName("Enemy"));
	
	CurrentHP=MaxHP;

	MetinSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(MetinSphereComponent);
	MetinStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MetinMesh"));
	MetinStaticMesh->SetupAttachment(GetRootComponent());
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(TEXT("HealtBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	
	Spawn1=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn1"));
	Spawn1->SetupAttachment(GetRootComponent());
	Spawn2=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn2"));
	Spawn2->SetupAttachment(GetRootComponent());
	Spawn3=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn3"));
	Spawn3->SetupAttachment(GetRootComponent());
	Spawn4=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn4"));
	Spawn4->SetupAttachment(GetRootComponent());
	Spawn5=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn5"));
	Spawn5->SetupAttachment(GetRootComponent());
	Spawn6=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn6"));
	Spawn6->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AMetinStone::BeginPlay()
{
	Super::BeginPlay();
	
	HealthBarWidget =Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
	HealthBarWidgetComponent->SetVisibility(false);
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
}

// Called every frame
void AMetinStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMetinStone::Interact(APlayerCharacter* PlayerCharacter)
{
}

void AMetinStone::GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult,
	EDamageTypes DamageType, ESkillDamageEffectTypes DamageEffectType, float Damage, float DamageDuration,
	float DamageTickRate)
{
	UE_LOG(LogTemp,Warning,TEXT("dAMAGE ALINDI"));
	if(!HealthBarWidgetComponent->IsVisible())
	{
		HealthBarWidgetComponent->SetVisibility(true);
	}
	float Value=CurrentHP-Damage;
	CurrentHP=UKismetMathLibrary::Clamp(Value,0,MaxHP);
	UpdateWidgetHpPercent();
	HandleSpawn();
	if(CurrentHP == 0) DestroyAction();
}

void AMetinStone::DestroyAction()
{
	if(DestroyExplosionVFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DestroyExplosionVFX,GetActorLocation());
	}
	Destroy();
}

float AMetinStone::GetCurrentHpPercent() const
{
	return CurrentHP/MaxHP;
}

void AMetinStone::UpdateWidgetHpPercent()
{
	if(HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(GetCurrentHpPercent());
	}
}

void AMetinStone::HandleSpawn()
{
	if(GetCurrentHpPercent()<= 0.8 && !bPhase1Started)
	{
		ChoosePhase(1);
		bPhase1Started = true;
	}
	if(GetCurrentHpPercent()<= 0.5 && !bPhase2Started)
	{
		ChoosePhase(2);
		bPhase2Started = true;
	}
	if(GetCurrentHpPercent()<= 0.2 && !bPhase3Started)
	{
		ChoosePhase(3);
		bPhase3Started = true;
	}
}

void AMetinStone::ChoosePhase(int32 PhaseNumber)
{
	switch (PhaseNumber)
	{
	default:
		//
		break;
	case 1 :
		SpawnPhase(Phase1Class);
		break;
	case 2 :
		SpawnPhase(Phase2Class);
		break;
	case 3 :
		SpawnPhase(Phase3Class);
		break;
	}
}

void AMetinStone::SpawnPhase(TSubclassOf<AHANEDANRPG3Character> SpawnClass)
{
	if(SpawnClass == nullptr) return;
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn1->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn1->GetComponentLocation());
	}
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn2->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn2->GetComponentLocation());
	}
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn3->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn3->GetComponentLocation());
	}
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn4->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn4->GetComponentLocation());
	}
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn5->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn5->GetComponentLocation());
	}
	GetWorld()->SpawnActor<AHANEDANRPG3Character>(SpawnClass,Spawn6->GetComponentLocation(),FRotator::ZeroRotator);
	if(SpawnVFXClass)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SpawnVFXClass,Spawn6->GetComponentLocation());
	}
}

