// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.h"
#include "Queque.generated.h"

UCLASS()
class MATCH3_API AQueque : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQueque();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AFloor*> GameFloors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AFloor* MovingFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AFloor> FloorClass;

	/** The size of a space on the grid. Does not include borders or spacing between tiles. */
	UPROPERTY(EditAnywhere, Category = Tile)
		FVector2D FloorSize;

	/** Get the world location for a given grid address. */
	UFUNCTION(BlueprintCallable, Category = Tile)
		FVector GetLocationFromFloorNo(int32 FloorNo) const;

	/** Get the world location for a given grid address. */
	UFUNCTION(BlueprintCallable, Category = Tile)
		AFloor* GetLastFloor() const		{
		return GameFloors.Last();
		}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void vWhenStop();

	AFloor* CreateFloor(TSubclassOf<class AFloor> FloorToSpawn, FVector SpawnLocation);
	
};
