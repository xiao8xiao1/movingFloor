// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Match3.h"
#include "Floor.h"


AFloor::AFloor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (RootComponent)
	{
		RootComponent->SetMobility(EComponentMobility::Movable);
	}
}

void AFloor::StartFalling(float FallDistance)
{
	FallingStartTime = GetWorld()->GetTimeSeconds();
	FallingStartLocation = GetActorLocation();
	// Tiles fall at a fixed rate of 120 FPS.
	GetWorldTimerManager().SetTimer(TickFallingHandle, this, &AFloor::TickFalling, 0.001f, true);
	TotalFallingTime = 0.75f;
	FallingEndLocation = FallingStartLocation + FallDistance;
}

void AFloor::TickFalling()
{
	float FallCompleteFraction = (GetWorld()->GetTimeSeconds() - FallingStartTime) / TotalFallingTime;

	if (FallCompleteFraction >= 1.0f)
	{
		FinishFalling();
	}
	else
	{
		FVector NewLocation = FMath::Lerp(FallingStartLocation, FallingEndLocation, FallCompleteFraction);
		SetActorLocation(NewLocation);
	}
}

void AFloor::FinishFalling()
{
	GetWorldTimerManager().ClearTimer(TickFallingHandle);
	SetActorLocation(FallingEndLocation);
//	Grid->OnTileFinishedFalling(this, LandingGridAddress);

}
