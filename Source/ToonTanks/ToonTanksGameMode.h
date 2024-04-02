// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

public:
	void ActorDied(class ABasePawn* DeadPawn);

private:
	float StartGameDelay = 3.f;
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;

	void HandleGameStart();
};
