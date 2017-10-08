// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RotateSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5; //Sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxRotationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float minRotationDegrees = 0;
	
	
	
};
