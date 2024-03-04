// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HANEDANRPG3/Structs/WeaponStruct.h"
#include "BaseWeapon.generated.h"

class UTraceComponent;
/**
 * 
 */
UCLASS()
class HANEDANRPG3_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	virtual void Tick(float DeltaTime) override;

	//COMPONENTS

	
	//FUNCTIONS

	//* Attach this weapon to target actor
	/* attackactortocomponent fonksiyonundaki socketnameyi weaponstructtan alıyor
	*/
	UFUNCTION(BlueprintCallable)
	virtual void EquipToBack(USceneComponent* InSceneComponent);

	UFUNCTION(BlueprintCallable)
	virtual void EquipToHand(USceneComponent* InSceneComponent);

	AActor* GetAttachedActor() const;
	
	//VARIABLES

	/** Dual wepaon ise true ya setlenmelidir */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = Initialize)
	bool bIsDualWeapon = false;

	//Structs
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Structs")
	FWeaponStruct WeaponStruct;
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//COMPONENTS
	//FUNCTIONS
	//VARIABLES

private:
	
	//COMPONENTS

	//** Weapon Mesh */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* WeaponStaticMeshComponent;

	/** 2 li silahlar için */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* WeaponStaticMeshComponent2;

	//** Weapon Trace Component */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UTraceComponent* WeaponTraceComponent;
	//FUNCTIONS
	
	//VARIABLES

public:
	FORCEINLINE UStaticMeshComponent* GetWeaponMeshComponent() const {return WeaponStaticMeshComponent;}
	FORCEINLINE UStaticMeshComponent* GetWeaponMeshComponent2() const {return WeaponStaticMeshComponent2;}
	FORCEINLINE void SetWeaponStaticMesh(UStaticMesh* StaticMesh) {WeaponStaticMeshComponent->SetStaticMesh(StaticMesh);}
	FORCEINLINE void SetWeaponStaticMesh2(UStaticMesh* StaticMesh) {WeaponStaticMeshComponent2->SetStaticMesh(StaticMesh);}
	FORCEINLINE UTraceComponent* GetWeaponTraceComponent() const  {return WeaponTraceComponent;}
	
};
