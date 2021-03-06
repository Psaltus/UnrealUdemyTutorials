// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	//virtual FVector CalculateMovement(FVector OriginalLocation, FVector TargetLocation);

	UPROPERTY(EditAnywhere)
	float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

	
private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	FVector Direction;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	
};
