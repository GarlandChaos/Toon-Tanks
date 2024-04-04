// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */

enum class EGameState
{
	SETUP,
	PLAYING,
	PAUSED,
	GAME_OVER
};

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(class ABasePawn* DeadPawn);
	EGameState GetGameState() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowMainMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(bool bWonGame);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Start Game")
	float StartGameDelay = 3.f;

	UFUNCTION(BlueprintCallable)
	void HandleGameStart();

private:
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;
	int32 TowerCount = 0;
	EGameState CurrentGameState = EGameState::SETUP;

	void SetGameState(EGameState NewGameState);
	int32 GetTowerCount() const;
};
