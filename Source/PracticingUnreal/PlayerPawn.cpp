// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D actorPosition2D = FVector2D(GetActorTransform().GetLocation());
	FVector2D mouseHitPosition2D = FVector2D(_cameraPawn->mouseHitPosition);

	// Rotate towards mouse hit position
	FVector direction = _cameraPawn->mouseHitPosition - GetActorTransform().GetLocation();
	direction.Normalize();
	SetActorRotation(direction.Rotation());

	// Distance between playerPawn and mouse location
	float distance = FVector2D::Distance(actorPosition2D, mouseHitPosition2D);

	//UE_LOG(LogTemp, Log, TEXT("%f"), distance * 0.5f);

	FVector velocity = direction * FMath::Max(distance * speedMultiplier, minimumSpeed);

	// Removing vertical axis
	FVector velocity2D = FVector(velocity.X, velocity.Y, 0.0f);

	// Set velocity
	_pawnMovement->Velocity = velocity2D;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

