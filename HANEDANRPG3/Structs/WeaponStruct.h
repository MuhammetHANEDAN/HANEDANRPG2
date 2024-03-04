// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "WeaponStruct.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct HANEDANRPG3_API FWeaponStruct : public FItemStruct
{
public:
	GENERATED_BODY()
	
	FWeaponStruct();
	~FWeaponStruct();
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECombatType CombatType=ECombatType::Ect_None;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BaseDamage=0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WeaponTraceRadius=0;
		
	/** Normal Attack için gerekli Staminayı buradan çek */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float NormalAttackStaminaCost=10;

	/** Normal Attack için gerekli manayı buradan çek */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float NormalAttackManaCost=0;

	/** skill için gerekli manayı buradan çek */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SkillManaCost=20;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName AttachSocketName2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName HandSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName HandSocketName2;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName MeshStartSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName MeshEndSocketName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* DrawAnimMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* DisArmAnimMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimMontage*> SkillMontages;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* SlideMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* RollMontage;

	/** Karakter targetingde değilken attığı dodge hareketi için */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* RollForwardMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* GuardingMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* KnockOutMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* KnockOutLoopMontage;
	
};

