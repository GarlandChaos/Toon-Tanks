// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();

	/*UPROPERTY(VisibleAnywhere)
	int32 VisibleAnywhereInt = 5;

	UPROPERTY(VisibleInstanceOnly)
	float VisibleInstanceOnlyFloat = 5.5f;

	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultsOnlyInt = 20;

	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt = 25;

	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnlyInt = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EditAnywhereFloat = 10.5f;*/

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass = NULL;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	class UParticleSystem* DeathParticleSystem = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* DeathSoundBase = nullptr;
};