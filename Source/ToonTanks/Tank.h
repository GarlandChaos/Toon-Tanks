// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();
	bool IsAlive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float TurretRotationSpeed = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Move(float Value);
	void Rotate(float Value);

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComponent = nullptr;

private:
	bool bIsAlive = true;
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;
};
