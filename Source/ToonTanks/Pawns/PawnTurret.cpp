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
}

void APawnTurret::CheckFireCondition()
{
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn) { return; }
	// If Player Player IS in range THEN FIRE!!!
	if (ReturnDistanceToPlayer()<=FireRange)
	{
		// Fire
		UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	// Check if we have a valid reference to the player.
	if (!PlayerPawn) { return 0.f; }

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	return Distance;
}
