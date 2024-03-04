// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

class AHANEDANRPG3GameMode;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="UFunctionLibrary||Getters")
	static AHANEDANRPG3GameMode* GetGameMode(UObject* WorldContext);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="UFunctionLibrary||Getters")
	static APlayerController* GetPlayerController(UObject* WorldContext);
	

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="UFunctionLibrary||Getters")
	static APlayerCharacter* GetPlayerCharacter(UObject* WorldContext);
	
};
