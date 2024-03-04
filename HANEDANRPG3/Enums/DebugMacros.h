#pragma once

#include "DrawDebugHelpers.h"
// #include "Enums/DebugMacros.h"
//meta=(AllowPrivateAccess="true")
//UE_LOG(LogTemp,Warning,TEXT(" worked"));
//GEngine->AddOnScreenDebugMessage
/*
* FString BoolAsString = FString::Printf(TEXT("%s"), bIsDragonBeingDriven() ? TEXT("true") : TEXT("false"));
 UE_LOG(LogTemp,Warning,TEXT(" %s worked"),*BoolAsString);
 */
//COMPONENTS


//FUNCTIONS


//VARIABLES



#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,20,12,FColor::Blue,false,3);
#define DRAW_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,100,12,FColor::Blue,false,-1.f);

#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 15);
#define DRAW_LINE_SingleFrame(StartLocation, EndLocation)  if (GetWorld()) \
{ \
DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f); \
}

#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,10,FColor::Red,false,15);
#define DRAW_POINT_SingleFrame(Location) if(GetWorld()) \
{ \
DrawDebugPoint(GetWorld(),Location,10,FColor::Red,false,-1.f); \
}

#define DRAW_VECTOR(StartLocation,EndLocation) if(GetWorld()) \
{ \
DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 15); \
DrawDebugPoint(GetWorld(),EndLocation,10,FColor::Red,false,15); \
}
#define DRAW_VECTOR_SingleFrame(StartLocation,EndLocation) if(GetWorld()) \
{ \
DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f); \
DrawDebugPoint(GetWorld(),EndLocation,10,FColor::Red,false,-1.f); \
}