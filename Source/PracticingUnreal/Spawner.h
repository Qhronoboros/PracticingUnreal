// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraPawn.h"
#include "Spawner.generated.h"

UCLASS()
class PRACTICINGUNREAL_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> _actorToSpawn;

	// +spawnOffset = closer to center, -spawnOffset = away from center
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _spawnOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnActor(const TArray<FVector> linePoints , const FVector centerPosition);
};
