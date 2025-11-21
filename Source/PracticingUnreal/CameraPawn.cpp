// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

bool ACameraPawn::GetLineTraceHit(FVector location, FVector direction, FHitResult& hit)
{
	FCollisionQueryParams collisionParams;
	DrawDebugLine(GetWorld(), location, location + direction * 10000.0f, FColor::Blue, false, 5.0f);
	if (!GetWorld()->LineTraceSingleByChannel(hit, location, location + direction * 10000.0f, ECC_Visibility, collisionParams)) return false;

	//UE_LOG(LogTemp, Log, TEXT("%s"), *hit.Location.ToString());

	return true;
}

bool ACameraPawn::GetMouseLineTraceHit(FHitResult& hit)
{
	FVector worldLocation;
	FVector worldDirection;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(worldLocation, worldDirection);

	return GetLineTraceHit(worldLocation, worldDirection, hit);
}

void ACameraPawn::ReceiveViewportCorners()
{
	FVector2D viewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(viewportSize);

	// The four corners of the viewport
	FVector2D viewportLocations[4] =
	{
		{ 0.0f, viewportSize.Y },
		{ viewportSize },
		{ 0.0f, 0.0f },
		{ viewportSize.X, 0.0f }
	};

	FHitResult hit[4];
	
	for (int i = 0; i < 4; i++)
	{
		FVector worldLocation;
		FVector worldDirection;
		//UE_LOG(LogTemp, Log, TEXT("%s"), *viewportLocations[i].ToString());
		GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(viewportLocations[i].X, viewportLocations[i].Y, worldLocation, worldDirection);
		if (!GetLineTraceHit(worldLocation, worldDirection, hit[i]))
		{
			UE_LOG(LogTemp, Warning, TEXT("Trace did not hit an object for getting one of the corners"));
		}
	}

	topLeftWorldCorner = hit[0].Location;
	topRightWorldCorner = hit[1].Location;
	bottomLeftWorldCorner = hit[2].Location;
	bottomRightWorldCorner = hit[3].Location;
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hit;
	if (!GetMouseLineTraceHit(hit)) return;

	mouseHitPosition = hit.Location;
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

