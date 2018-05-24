// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Match3.h"
#include "Queque.h"


// Sets default values
AQueque::AQueque()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector AQueque::GetLocationFromFloorNo(int32 FloorNo) const
{
	FVector OutLocation = GetActorLocation();
	OutLocation.Z -= FloorSize.Y * FloorNo;

	return OutLocation;
}

// Called when the game starts or when spawned
void AQueque::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQueque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//From MovingFloor produce two Floor, one delete, one drop,MovingFloor shrink
void AQueque::vWhenStop()
{
	AFloor* TopFloor = GameFloors.Top();
	if (TopFloor == NULL || MovingFloor == NULL)
		return;
	MovingFloor->SetActorHiddenInGame(true);

	float width = MovingFloor->GetActorScale3D().X;
	float movFloorPosX = MovingFloor->GetActorLocation().X;
	float topFloorPosX = TopFloor->GetActorLocation().X;
	float diffPos = movFloorPosX - topFloorPosX;
	//end game
	if (FMath::Abs(diffPos) >= width) {
		return;
	}
	float leftPos, rightPos, dropPos, dropWidth, delPos, delWidth;
	//no need two Floor
	if (diffPos == 0)
	{
		MissAndEnd();
	}
	else
	{
		if (diffPos < 0) {
			leftPos = topFloorPosX - width / 2;
			rightPos = movFloorPosX + width / 2;

			dropPos = (leftPos + rightPos) / 2;
			dropWidth = rightPos - leftPos;

			delPos = leftPos + diffPos / 2;
			delWidth = diffPos * (-1) ;
		}
		else if (diffPos > 0)
		{
			leftPos = movFloorPosX - width / 2;
			rightPos = topFloorPosX + width / 2;

			dropPos = (leftPos + rightPos) / 2;
			dropWidth = rightPos - leftPos;

			delPos = rightPos + diffPos / 2;
			delWidth = diffPos ;
		}
		FVector location = MovingFloor->GetActorLocation();
		location.X = dropPos;
		AFloor* DropFloor = CreateFloor(FloorClass, location);
		FVector scale = MovingFloor->GetActorScale3D();
		scale.X = dropWidth;
		DropFloor->SetActorScale3D(scale);

		location = MovingFloor->GetActorLocation();
		location.X = delPos;
		AFloor* DelFloor = CreateFloor(FloorClass, location);
		scale.X = delWidth;
		DelFloor->SetActorScale3D(scale);

		GameFloors.Add(DropFloor);
		StartFalling();
		//falling 0.5s, disable input
	}


}


AFloor* AQueque::CreateFloor(TSubclassOf<class AFloor> FloorToSpawn, FVector SpawnLocation)
{
	// If we have set something to spawn:
	if (FloorToSpawn)
	{
		// Check for a valid World:
		UWorld* const World = GetWorld();
		if (World)
		{
			// Set the spawn parameters.
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			// Spawn the tile.
			AFloor* const NewFloor = World->SpawnActor<AFloor>(FloorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
			NewFloor->GetRenderComponent()->SetMobility(EComponentMobility::Movable);
			return NewFloor;
		}
	}
	return nullptr;
}



void AQueque::StartFalling(float FallDistance)
{
	FallingStartTime = GetWorld()->GetTimeSeconds();
	// Tiles fall at a fixed rate of 120 FPS.
	GetWorldTimerManager().SetTimer(TickFallingHandle, this, &AQueque::TickFalling, 0.001f, true);
	TotalFallingTime = 0.75f;

	for(floor : GameFloors)
		floor->StartFalling(FloorHeight);
	
}

void AQueque::TickFalling()
{
	float FallCompleteFraction = (GetWorld()->GetTimeSeconds() - FallingStartTime) / TotalFallingTime;

	for(floor : GameFloors)
		floor->TickFalling(FallCompleteFraction);

	if (FallCompleteFraction >= 1.0f)
	{
		FinishFalling();
	}
	
}

void AQueque::FinishFalling()
{
	GetWorldTimerManager().ClearTimer(TickFallingHandle);
//	Grid->OnTileFinishedFalling(this, LandingGridAddress);

}

