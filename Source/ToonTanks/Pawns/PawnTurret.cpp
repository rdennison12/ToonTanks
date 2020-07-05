// Copyright 2020 Rick Dennison


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// If the PlayerPawn reference isn't valid or it's out of range, return.
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }

	// If we have a PlayerPawn in range then rotate the turret to follow.
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive()) { return; }
	// If Player Player IS in range THEN FIRE!!!
	if (ReturnDistanceToPlayer()<=FireRange)
	{
		// Fire
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	// Check if we have a valid reference to the player.
	if (!PlayerPawn) { return 0.f; }

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	return Distance;
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}
