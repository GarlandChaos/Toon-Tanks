// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	class ATank* Tank = nullptr;
	FTimerHandle FireRateTimerHandle = FTimerHandle();
	float FireRate = 2.f;

	void CheckFireCondition();
	bool IsTargetWithinRange();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float TargetRange = 0.f;
};
