// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDamageTaken: DamagedActor: %s, Damage: %f, Instigator: %s"), *DamagedActor->GetName(), Damage, *Instigator->GetName());

	if (Damage <= 0.f || Health <= 0.f) return;

	Health -= Damage;

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("DamagedActor: %s, Health: %f"), *DamagedActor->GetName(), Health);
}