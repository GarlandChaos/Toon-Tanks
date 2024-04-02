// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(ABasePawn* DeadPawn)
{
	DeadPawn->HandleDestruction();
}

void AToonTanksGameMode::HandleGameStart()
{
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (!ToonTanksPlayerController) return;

	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle StartGameTimerHandle = FTimerHandle();
	FTimerDelegate StartGameTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(StartGameTimerHandle, StartGameTimerDelegate, StartGameDelay, false);
}