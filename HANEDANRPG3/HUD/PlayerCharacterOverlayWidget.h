// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacterOverlayWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API UPlayerCharacterOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;
	
public:
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* SPProgressBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* StaminaProgressBar;
	
};
