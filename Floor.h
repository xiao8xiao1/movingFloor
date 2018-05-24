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
private:
	FVector FallingStartLocation;
	FVector FallingEndLocation;
};
