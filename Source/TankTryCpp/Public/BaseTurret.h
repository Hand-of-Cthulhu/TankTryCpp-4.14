// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TankStateCpp.h"
#include "Animation/AnimInstance.h"
#include "BaseTurret.generated.h"

UCLASS()
class TANKTRYCPP_API ABaseTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTurret();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& changedEvent) override;

	UPROPERTY(BlueprintReadOnly, Category = Components)
		USceneComponent* sceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USkeletalMeshComponent* mainTurretSke;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UCameraComponent* eyeCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystemComponent* bulletPartic;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystemComponent* muzzleFlashPartic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
		float damagePerShot = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
		TSubclassOf<UDamageType> dmgType;

	UPROPERTY(BlueprintReadOnly, Category = Animation)
		float turretYaw = 0;
	UPROPERTY(BlueprintReadOnly, Category = Animation)
		float turretTruePitch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UAnimMontage* gunFireMont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float fireRPM = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float gunHeatPerShot = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float gunCooldownSpeed = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float maxInaccuracy = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TArray<TEnumAsByte<ECollisionChannel>> bulletBlockers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
		UParticleSystem* bulletHitPartic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
		UMaterialInterface* bulletHitDecal;


	void BeginFiring();
	void StopFiring();
	void FireGun();

	void PassAlongSomeStuff(ATankStateCpp* playerTankState);

protected:
	ATankStateCpp* tankState;
	FCollisionObjectQueryParams objQuery;
	FCollisionQueryParams colQuery;
	UAnimInstance* animationInst;

	//OverridableFuncs
	virtual void ParticleEfx(FVector trueAimLoc);

private:
	FTimerHandle firingTimer;
	bool timerPausePend = false;
	float spreadXVal = 0;
};
