// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SpawnOrDestroyDamageActor.h"

#include "Actors/DamageActor.h"
#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "Particles/ParticleSystemComponent.h"

void UAN_SpawnOrDestroyDamageActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	AActor* OwnerActor = MeshComp->GetOwner();
	if(OwnerActor==nullptr) return;
	AHANEDANRPG3Character* OwnerCharacter = Cast<AHANEDANRPG3Character>(OwnerActor);
	if(OwnerCharacter==nullptr) return;
	if(bSpawmOrDestroy)
	{
		if(DamageActorClass==nullptr) return;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner=OwnerActor;
		const FVector StartLocation = FVector(0,0,-100);
		ADamageActor* SpawnedActor = OwnerActor->GetWorld()->SpawnActor<ADamageActor>(DamageActorClass,StartLocation,FRotator::ZeroRotator, SpawnParameters);
		ensureMsgf(SpawnedActor != nullptr, TEXT("SpawnActor failed!"));
		if(SpawnedActor==nullptr) return;
		OwnerCharacter->ActiveSkillDamageActor=SpawnedActor;
	}
	else
	{
		if(OwnerCharacter->ActiveSkillDamageActor)
		{
			OwnerCharacter->ActiveSkillDamageActor->Destroy();
			OwnerCharacter->ActiveSkillDamageActor=nullptr;
		}
		if(OwnerCharacter->ActiveSkillVFXComponent)
		{
			const bool bActive = OwnerCharacter->ActiveSkillVFXComponent->IsActive();
			if(bActive)
			{
				OwnerCharacter->ActiveSkillVFXComponent->Deactivate();
			}
		}
	}
}
