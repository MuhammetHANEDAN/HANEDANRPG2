// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

class APlayerCharacter;
class AHANEDANRPG3Character;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HANEDANRPG3_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(APlayerCharacter* PlayerCharacter )=0;
	/*virtual void GetHit(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, float Damage, float DamageDuration, float
	                    DamageTickRate)=0;*/
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractInterface")
	void GetHit(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes
	            DamageEffectType, float Damage, float DamageDuration, float DamageTickRate);
	
	virtual void GetHit_Implementation(AActor* DamageCauserActor, const FHitResult& OutHitResult, EDamageTypes DamageType, ESkillDamageEffectTypes
	                                   DamageEffectType, float Damage, float DamageDuration, float DamageTickRate)
	{
		
	}

};
