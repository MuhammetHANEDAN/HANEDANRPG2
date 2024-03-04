// Fill out your copyright notice in the Description page of Project Settings.


#include "HANEDANRPG3/HUD/MainHUD/MainHUD.h"

#include "Blueprint/UserWidget.h"
#include "HANEDANRPG3/HUD/PlayerCharacterOverlayWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	World=GetWorld();
	if(World == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("world oluştrulamadı"))
		return;
	}
	
	PlayerController=World->GetFirstPlayerController();
	if(PlayerController == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("controller oluştrulamadı"))
	}
	
	PlayerCharacterOverlayWidget = CreateWidget<UPlayerCharacterOverlayWidget>(PlayerController, PlayerCharacterOverlayWidgetClass);
	if(PlayerCharacterOverlayWidget)
	{
		PlayerCharacterOverlayWidget->AddToViewport();
	}
}
