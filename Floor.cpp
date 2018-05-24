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
	FallingStartLocation = GetActorLocation();
	FallingEndLocation = FallingStartLocation + FallDistance;
}

void AFloor::TickFalling(float FallCompleteFraction )
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
