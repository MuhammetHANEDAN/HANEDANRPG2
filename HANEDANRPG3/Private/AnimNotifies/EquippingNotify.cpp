// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/EquippingNotify.h"

#include "HANEDANRPG3/HANEDANRPG3Character.h"
#include "HANEDANRPG3/Items/BaseWeapon.h"

void UEquippingNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if(AHANEDANRPG3Character* PlayerCharacter = Cast<AHANEDANRPG3Character>(MeshComp->GetOwner()))
	{
		if(bEquipOrDisEquip)
		{
			PlayerCharacter->DrawWeapon();
			PlayerCharacter->CombatType=PlayerCharacter->MainWeapon->WeaponStruct.CombatType;
		}
		else
		{
			PlayerCharacter->PutBackWeapon();
			PlayerCharacter->CombatType=ECombatType::Ect_None;
		}
	}
}
