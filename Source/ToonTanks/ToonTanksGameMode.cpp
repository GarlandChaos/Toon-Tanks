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

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(ABasePawn* DeadPawn)
{
	DeadPawn->HandleDestruction();

	if (ATower* DeadTower = Cast<ATower>(DeadPawn))
	{
		TowerCount = FMath::Clamp(--TowerCount, 0.f, INT_MAX);

		if (TowerCount > 0) return;

		EndGame(true);
	}
	else if (ATank* DeadTank = Cast<ATank>(DeadPawn))
	{
		EndGame(false);
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	TowerCount = GetTowerCount();
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (!ToonTanksPlayerController) return;

	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle StartGameTimerHandle = FTimerHandle();
	FTimerDelegate StartGameTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(StartGameTimerHandle, StartGameTimerDelegate, StartGameDelay, false);
}

int32 AToonTanksGameMode::GetTowerCount()
{
	TArray<AActor*> Towers = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}