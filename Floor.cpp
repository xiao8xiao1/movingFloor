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

void AFloor::SetStartFalling(float FallDistance)
{
	FallingStartLocation = GetActorLocation();
	FallingEndLocation = FallingStartLocation;
	FallingEndLocation.Z += FallDistance;
}

void AFloor::SetTickFalling(float FallCompleteFraction )
{
	if (FallCompleteFraction >= 1.0f)
	{
		SetActorLocation(FallingEndLocation);
	}
	else
	{
		FVector NewLocation = FMath::Lerp(FallingStartLocation, FallingEndLocation, FallCompleteFraction);
		SetActorLocation(NewLocation);
	}
}


void AFloor::StartFalling(float fallDistance, float delTime)
{
	FallingStartTime = GetWorld()->GetTimeSeconds();
	// Tiles fall at a fixed rate of 120 FPS.
	GetWorldTimerManager().SetTimer(TickFallingHandle, this, &AFloor::TickFalling, 0.001f, true);

	DelTime = delTime;
	FallingStartLocation = GetActorLocation();
	FallingEndLocation = FallingStartLocation;
	FallingEndLocation.Z += fallDistance;
}

void AFloor::TickFalling( )
{
	float FallCompleteFraction = (GetWorld()->GetTimeSeconds() - FallingStartTime) / DelTime;
	
	if (FallCompleteFraction >= 1.0f)
	{
		GetWorldTimerManager().ClearTimer(TickFallingHandle);	
		Destroy();
	}
	else
	{
		FVector NewLocation = FMath::Lerp(FallingStartLocation, FallingEndLocation, FallCompleteFraction);
		SetActorLocation(NewLocation);
	}
}
