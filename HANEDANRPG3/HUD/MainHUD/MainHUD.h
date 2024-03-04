// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UPlayerCharacterOverlayWidget;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(VisibleAnywhere, Category="Initialize")
	UWorld* World;

	UPROPERTY(VisibleAnywhere, Category="Initialize")
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, Category="Initialize")
	UPlayerCharacterOverlayWidget* PlayerCharacterOverlayWidget;
	
	
	UPROPERTY(EditDefaultsOnly, Category="PlayerCharacter")
	TSubclassOf<UPlayerCharacterOverlayWidget> PlayerCharacterOverlayWidgetClass;
};
