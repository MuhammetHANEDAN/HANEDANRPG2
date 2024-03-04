// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class HANEDANRPG3_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	//COMPONENTS

	
	//FUNCTIONS

	
	//VARIABLES

	//STRUCTS

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//COMPONENTS
	//FUNCTIONS
	//VARIABLES
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//COMPONENTS
	//FUNCTIONS
	//VARIABLES
};
