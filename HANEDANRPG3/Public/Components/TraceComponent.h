// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HANEDANRPG3/Structs/WeaponStruct.h"
#include "TraceComponent.generated.h"


class AHANEDANRPG3Character;
class ABaseWeapon;

/**
 *Ett_MeshSockets ANS den meshteki socket isimleri verilir , Trace radius, Damage verilebilir,verilmezse defaultu alırlar. Eğer
 *tracecomponent bir hanedanrpg3 charactere direk bağlanmışsa ve karakter meshindeki socketler kullanılarak
 *trace çizdirilecekse seçilir.
 *
 * Ett_Weapon_SingleWeapon  ANS de socket name vermeye gerek yoktur. Weaponun.structtaki meshstart ve meshendnameye göre getsocketlocationbyname ile location alıp trace çizer
 * 
 * Ett_Weapon_DualWeapon   ANS de socket name vermeye gerek yoktur. bFirstWeapon vermek yeterlidir.
 */
UENUM(BlueprintType)
enum class ETraceType : uint8
{
	Ett_MeshSockets UMETA(DisplayName="MeshSockets"),
	Ett_Weapon_SingleWeapon UMETA(DisplayNmae="SingleWeapon"),
	Ett_Weapon_DualWeapon UMETA(DisplayNmae="DualWeapon")
};

/** Component eklendiğinde enum değeri uygun olarak seçilmelidir.Component handeanrpg3character base classı için dizayn edildi */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HANEDANRPG3_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraceComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//FUNCTIONS
	
	void Initialize();
	
	UFUNCTION(BlueprintCallable)
	void EnableTrace();
	
	void DisableTrace();

	void Tracing(const FVector &StartLocation, const FVector &EndLocation);

	/** Tracecomponent direk bir hanedanrpg3 charactere ekli ise o karakter meshinde bulunan socketlerin locationunu verir girilen socketnameye göre */
	FVector GetMeshSocketLocation(FName InSocketName) const ;

	/** Karakter mainweaponunda bulunan socketleri verilen socketnameler sayesinde çeker */
	FVector GetWeaponSocketLocation(FName InSocketName) const ;

	/** Eğer Dual sword gibi bir silah için trace çizdirilecekse baseweaponda bulunan 2. static meshteki socket locationları almak için kullanılır */
	FVector GetWeaponSocketLocation2(FName InSocketName) const ;
	
	//VARIABLES

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	ETraceType TraceType;

	bool bMeshSocketsTrace = false;
	bool bSingleWeaponTrace = false;
	bool bDualWeaponTrace = false;

	/** Eğer tracetype dualweapon seçilirse ANS de bDualweapon true olacak sonra ANS de olan bFirstWeapon değeriyle bu setlenecek
	 *ve ilkmi yoksa ikinci eldeki silahtamı trace çizdirileceği belli olacak
	 */
	bool bFirstWeapon = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bShouldTrace=false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float TraceRadius = 50;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Damage = 10;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AActor* OwnerActor;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AHANEDANRPG3Character* OwnerCharacter;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FWeaponStruct  OwnerWeaponStruct;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float  OwnerBuffedDamage = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FName MeshSocketStartName;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FName MeshSocketEndName;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ABaseWeapon* OwnerWeapon;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UObject* WorldContextObject;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AActor*> HittedActors;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<FHitResult> HitResults;
	

	FTimerHandle DelayTimerHandle;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
