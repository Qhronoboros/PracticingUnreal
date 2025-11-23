// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnActor(const TArray<FVector> linePoints, const FVector centerPosition)
{
	// Line = point A to point B
	// Full line = point A to point B to point ... back to point A
	
	// Find a random point on the full line
	int linePointAmount = linePoints.Num();
	if (linePointAmount == 0) return;

	float lineFractonLength = 1.0f / linePointAmount;
	float randomPointOnFullLine = FMath::FRand() / lineFractonLength;

	int startingPoint = FMath::FloorToInt(randomPointOnFullLine);
	float positionOnLine = FMath::Frac(randomPointOnFullLine);

	FVector spawnPosition = FMath::Lerp(linePoints[startingPoint],
		linePoints[(startingPoint + 1) % linePointAmount], positionOnLine);
	
	// Extra offset using the center point direction of the full line
	FVector centerDirection = centerPosition - spawnPosition;
	centerDirection.Normalize();

	spawnPosition += centerDirection * _spawnOffset;

	// Left and right direction from the centerDirection
	FVector rightDirection = centerDirection.Cross(FVector::UpVector);
	FVector leftDirection = -rightDirection;
	
	// Find two points within the full line that are closest to the right or left rotation/direction angle-wise
	FVector rightPointDirection, leftPointDirection;
	float biggestRightDotProduct = -1.0f, biggestLeftDotProduct = -1.0f;

	for (FVector linePoint : linePoints)
	{
		FVector direction = linePoint - spawnPosition;
		direction.Normalize();

		float rightDotProduct = rightDirection.Dot(direction);
		if (rightDotProduct > biggestRightDotProduct)
		{
			rightPointDirection = direction;
			biggestRightDotProduct = rightDotProduct;
		}

		float leftDotProduct = leftDirection.Dot(direction);
		if (leftDotProduct > biggestLeftDotProduct)
		{
			leftPointDirection = direction;
			biggestLeftDotProduct = leftDotProduct;
		}
	}

	// Get random angle between points
	FVector randomDirection = FVector::SlerpNormals(rightPointDirection, leftPointDirection, FMath::FRand());

	// spawn projectile
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* projectile = GetWorld()->SpawnActor<AActor>(_actorToSpawn, spawnPosition, randomDirection.Rotation(), spawnParams);
}