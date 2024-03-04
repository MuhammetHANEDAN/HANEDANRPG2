// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct HANEDANRPG3_API FItemStruct
{
public:
	GENERATED_BODY()
	FItemStruct();
	~FItemStruct();


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EItemType ItemType=EItemType::Eit_None;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ItemNumber=0;

	
};
