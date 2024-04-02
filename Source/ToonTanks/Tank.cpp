// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksPlayerController = GetController<AToonTanksPlayerController>();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ToonTanksPlayerController) return;

	FHitResult HitResult;
	ToonTanksPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	RotateTurret(HitResult.ImpactPoint);

	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 12, FColor::Magenta);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Rotate);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	ToonTanksPlayerController->SetPlayerEnabledState(false);
	/*DisableInput(PlayerController);
	PlayerController->bShowMouseCursor = false;*/
}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("%f"), Value);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Rotate(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("%f"), Value);

	//float AngleRad = FMath::DegreesToRadians(Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this));
	//FQuat DeltaRotation(FVector::UpVector, AngleRad);
	//AddActorLocalRotation(DeltaRotation, true);

	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}