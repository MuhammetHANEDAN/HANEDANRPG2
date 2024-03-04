// Copyright Epic Games, Inc. All Rights Reserved.

#include "HANEDANRPG3GameMode.h"
#include "UObject/ConstructorHelpers.h"

AHANEDANRPG3GameMode::AHANEDANRPG3GameMode()
{
	
}

/*
 set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter_C"));
if (PlayerPawnBPClass.Class != NULL)
{
	DefaultPawnClass = PlayerPawnBPClass.Class;
}
 */

void AHANEDANRPG3GameMode::StartPlay()
{
	Super::StartPlay();
	
}
