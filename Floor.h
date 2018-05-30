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
	void SetStartFalling(float FallDistance);
	void SetTickFalling(float FallCompleteFraction );
	void StartFalling(float fallDistance, float delTime);
	void TickFalling();
private:
	FVector FallingStartLocation;
	FVector FallingEndLocation;
	float DelTime;	
	float FallingStartTime;
	FTimerHandle TickFallingHandle;
};
