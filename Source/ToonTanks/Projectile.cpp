// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->MaxSpeed = 5000.f;
	ProjectileMovementComponent->InitialSpeed = 1000.f;

	TrailParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Trail Particle System Component");
	TrailParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSoundBase, GetActorLocation(), 1.f, .5f);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*UE_LOG(LogTemp, Warning, TEXT("OnHit: OtherActor: %s, OtherComp: %s, NormalImpulse: %s"), *OtherActor->GetName(), *OtherComp->GetName(), *NormalImpulse.ToString());*/
	
	AController* OwnerInstigator = GetInstigator()->GetController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (!OtherActor || OtherActor == GetOwner() || OtherActor == this)
	{
		Destroy();
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleSystem, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	Destroy();
}