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

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(bool bWonGame);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Start Game")
	float StartGameDelay = 3.f;

public:
	void ActorDied(class ABasePawn* DeadPawn);

private:
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;
	int32 TowerCount = 0;

	void HandleGameStart();
	int32 GetTowerCount();
};
