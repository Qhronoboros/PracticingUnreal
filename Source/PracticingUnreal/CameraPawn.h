// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class PRACTICINGUNREAL_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector mouseHitPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector topLeftWorldCorner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector topRightWorldCorner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector bottomRightWorldCorner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector bottomLeftWorldCorner;

	UFUNCTION(BlueprintCallable)
	bool GetLineTraceHit(FVector location, FVector direction, FHitResult& hit);

	UFUNCTION(BlueprintCallable)
	bool GetMouseLineTraceHit(FHitResult& hit);

	UFUNCTION(BlueprintCallable)
	void ReceiveViewportCorners();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
