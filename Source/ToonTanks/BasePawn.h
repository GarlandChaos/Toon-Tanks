// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass = NULL;
};