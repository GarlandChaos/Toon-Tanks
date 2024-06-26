// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 50.f;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	class UParticleSystem* HitParticleSystem = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Visual Effects")
	class UParticleSystemComponent* TrailParticleSystemComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* HitSoundBase = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* LaunchSoundBase = nullptr;
};
