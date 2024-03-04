// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SpawnProjectileDamageActor.h"

#include "Actors/DamageActor.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "Kismet/KismetMathLibrary.h"

void UAN_SpawnProjectileDamageActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* OwnerActor = MeshComp->GetOwner();
	if(OwnerActor==nullptr) return;
	AHANEDANRPG3Character* OwnerCharacter = Cast<AHANEDANRPG3Character>(OwnerActor);
	if(OwnerCharacter==nullptr) return;
	
	if(bActorForwardOrMeshSocket)
	{
		const FVector ActorLocation = OwnerActor->GetActorLocation();
		const FVector ActorForwardVector = OwnerActor->GetActorForwardVector();
		const FVector StartLocation = ActorLocation+ActorForwardVector*100;
		FRotator StartRotation = UKismetMathLibrary::MakeRotFromX(ActorForwardVector);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner=OwnerActor;
		ADamageActor* SpawnedActor = OwnerActor->GetWorld()->SpawnActor<ADamageActor>(DamageActorClass,StartLocation,StartRotation, SpawnParameters);
	}
	else
	{
		const FVector StartLocation = OwnerCharacter->GetMesh()->GetSocketLocation(SocketName);
		const FVector ActorForwardVector = OwnerActor->GetActorForwardVector();
		FRotator StartRotation = UKismetMathLibrary::MakeRotFromX(ActorForwardVector);
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner=OwnerActor;
		ADamageActor* SpawnedActor = OwnerActor->GetWorld()->SpawnActor<ADamageActor>(DamageActorClass,StartLocation,StartRotation, SpawnParameters);
	}
}
