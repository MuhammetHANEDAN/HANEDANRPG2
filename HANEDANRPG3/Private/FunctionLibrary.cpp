// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary.h"

#include "HANEDANRPG3/HANEDANRPG3GameMode.h"
#include "HANEDANRPG3/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AHANEDANRPG3GameMode* UFunctionLibrary::GetGameMode(UObject* WorldContext)
{
	if(AHANEDANRPG3GameMode* Gamemode=Cast<AHANEDANRPG3GameMode>(UGameplayStatics::GetGameMode(WorldContext)))
	{
		return Gamemode;
	}
	return nullptr;
}

APlayerController* UFunctionLibrary::GetPlayerController(UObject* WorldContext)
{
	if(APlayerController* PlayerController=UGameplayStatics::GetPlayerController(WorldContext,0))
	{
		return PlayerController;
	}
	return nullptr;
}


APlayerCharacter* UFunctionLibrary::GetPlayerCharacter(UObject* WorldContext)
{
	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(WorldContext,0);
	if(APlayerCharacter* PlayerCharacter=Cast<APlayerCharacter>(Character))
	{
		return PlayerCharacter;
	}
	return nullptr;
}
