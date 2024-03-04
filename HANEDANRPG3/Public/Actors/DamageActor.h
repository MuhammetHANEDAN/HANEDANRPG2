// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HANEDANRPG3/Enums/Enums.h"
#include "DamageActor.generated.h"

class IInteractInterface;
class AHANEDANRPG3Character;

UCLASS()
class HANEDANRPG3_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
public:
	
	// Atılacak skillere genel olarak modülerlik kazanmak içn ufak bir çalışma yaptım her tür kendi alanına göre gerekli bilgileri içermekte

	/*
	Edat_AttachedDamageActor UMETA(DisplayNmae="AttachedDamageActor"),
	Edat_AttachedAuraActor UMETA(DisplayNmae="AttachedAuraActor"), // kullanmayacaz bu projede
	Edat_AttachedLocationDamageActor UMETA(DisplayNmae="AttachedLocationDamageActor"),
	Edat_AreaDirectDamage UMETA(DisplayNmae="AreaDirectDamage"),
	Edat_ProjectileDamageActor UMETA(DisplayNmae="ProjectileDamageActor")
	*/


	/**
	 * Seçilen DamageActorTypelara göre setlenmesi gerekn veriler  aşağıda açıklanmıştır
	 * 
	 * AttachedDamageActor için location BP den setlenmelidir.Spawnlanan vfx ve damage actor hanedanrpg3 base classta referans olarak tutulacaktır.
	 * Bu sayede destroy işlemi AN_SpawnorDestroyDamageActor ile yapılabilir
	 * 
	 * AttachedAuraActor için attach edileceği karakter meshindeki socket ismi belirtilmeli. Biz bu actoru bu oyunda kullanmadık o yüzden boş bıraktık.
	 * Destroy işlemi AN_SpawnorDestroyDamageActor ile yapılabilir.Şu an için hem attacheddamage ve attachedaura aynı anda kullanılamaz.
	 * Çünkü referansları ayrı ayrı tutulamaz.
	 * 
	 * AttachedLocationDamageActor Bp den location setlenmelidir.Destroy işlemide bp den yapılmalıdır.Spawn Distance setlenmelidir.
	 * 
	 * AreaDirectDamage ilk olarak locationu BP den  setlenmelidir.BP den overlap olan her actöre damage gönderilmelidir.Destroy işlemi
	 * DamageActorun içinden yapılmaktadır 0.1 saniye sonra destroylanır.Emitter Spawnı ve spawnlanacak locationda bp den yapılmalıdır.
	 * Spawn Distance setlenmelidir.
	 * 
	 * Projectile çarptığı anda destroy edilmeli BP den.ProjectileLifeTime default olarak 5 saniye olark belirlendi destroylamazsan
	 * 5 saniye içinde kendisini destroylar.Projectile için AN_Spawnprojectile da işlemler yapılacak.
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	EDamageActorType DamageActorType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	EDamageTypes DamageType;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	ESkillDamageEffectTypes DamageEffectType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UParticleSystem* SkillVfx;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName DamageActorSpawnLocationSocketName;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AHANEDANRPG3Character* OwnerCharacter;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AActor*>TargetActors;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float SkillSpCost=0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage=0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DamageTickRate=0;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DamageDuration=0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float SpawnDistance=500;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Projectile)
	float ProjectileLifeTime=5;

	FTimerHandle GeneralTimerHandle;

	/** İstenilen distanceye kadar karakterin forwardvectoru rotasyonunda linetrace çizer eğer damageable bir pawna çarparsa
	 *  ve o pawn Damageable tagına sahipse o pawnın locationunu döndürür bunlar sağlanmıyorsa karakterin önüne doğru spawndistance
	 *  kadar ilerisinin locationunu verir.
	 */
	UFUNCTION(BlueprintCallable)
	FVector LineTraceAndGetLocation() const ;

	UFUNCTION(BlueprintCallable)
	AHANEDANRPG3Character* GetOwnerCharacter() const ;

	UFUNCTION(BlueprintCallable)
	FVector GetTargetActorLocation(AActor* TargetActor) const ;

	UFUNCTION(BlueprintCallable)
	FRotator GetTargetActorRotation(AActor* TargetActor) const ;

	/** TargetActor valid ve targetactorde Damageable Tagi varsa damageyi yollar */
	UFUNCTION(BlueprintCallable)
	void DoDamageToTargetActor(AActor* TargetActor,FHitResult InHitResult);
	
	UFUNCTION(BlueprintCallable)
	virtual void DoDamageToTargetActors();
	
	//* owner characterdeki skillvfxcomponentti checkler sonra active olup olmamasına göre active etmektedir /*
	UFUNCTION(BlueprintCallable)
	void ActivateOwnerCharacterSkillVFX();
	
	//* owner characterdeki skillvfxcomponentti checkler sonra active olup olmamasına göre deactive etmektedir /*
	UFUNCTION(BlueprintCallable)
	void DeactivateOwnerCharacterSkillVFX();

	UFUNCTION(BlueprintCallable)
	void DestroyActor();

};
