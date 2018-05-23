// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Floor.generated.h"

/**
 * 
 */
UCLASS()
class MATCH3_API AFloor : public APaperSpriteActor
{
	GENERATED_BODY()
	
	
	
public:	
		AFloor();

	void StartFalling(float FallDistance);

	void TickFalling();

	void FinishFalling();

protected:
	float TotalFallingTime;
	FVector FallingStartLocation;

	float FallingStartTime;
	FVector FallingEndLocation;
	FTimerHandle TickFallingHandle;
};
