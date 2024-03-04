

#pragma once

#include "CoreMinimal.h"
#include "CharacterStatsStruct.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct HANEDANRPG3_API FCharacterStatsStruct
{
public:
	GENERATED_BODY()
	FCharacterStatsStruct();
	~FCharacterStatsStruct();


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP=0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHP=0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxStamina=0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentStamina=0;

	
};
