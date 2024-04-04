// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include <limits>

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	ShowMainMenu();
	//HandleGameStart();
}

void AToonTanksGameMode::ActorDied(ABasePawn* DeadPawn)
{
	DeadPawn->HandleDestruction();

	if (ATower* DeadTower = Cast<ATower>(DeadPawn))
	{
		TowerCount = FMath::Clamp(--TowerCount, 0.f, INT_MAX);

		if (TowerCount > 0) return;

		EndGame(true);
		CurrentGameState = EGameState::GAME_OVER;
	}
	else if (ATank* DeadTank = Cast<ATank>(DeadPawn))
	{
		EndGame(false);
		CurrentGameState = EGameState::GAME_OVER;
	}
}

EGameState AToonTanksGameMode::GetGameState() const
{
	return CurrentGameState;
}

void AToonTanksGameMode::HandleGameStart()
{
	CurrentGameState = EGameState::SETUP;
	TowerCount = GetTowerCount();
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (!ToonTanksPlayerController) return;

	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle SetupGameTimerHandle = FTimerHandle();
	FTimerDelegate SetupGameTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(SetupGameTimerHandle, SetupGameTimerDelegate, StartGameDelay, false);

	FTimerHandle StartGameTimerHandle = FTimerHandle();
	FTimerDelegate StartGameTimerDelegate = FTimerDelegate::CreateUObject(this, &AToonTanksGameMode::SetGameState, EGameState::PLAYING);
	GetWorldTimerManager().SetTimer(StartGameTimerHandle, StartGameTimerDelegate, StartGameDelay, false);
}

void AToonTanksGameMode::SetGameState(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
}

int32 AToonTanksGameMode::GetTowerCount() const
{
	TArray<AActor*> Towers = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}