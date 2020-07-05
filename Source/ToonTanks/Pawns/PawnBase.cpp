// Copyright 2020 Rick Dennison


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}


void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// Find Rotation value to look at. 
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z));

	// Rotate Turret.
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
	TempProjectile->SetOwner(this);
}

void APawnBase::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), FRotator::ZeroRotator);
	}
}

void APawnBase::PawnDestroyed()
{
	HandleDestruction();
}
