// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
class ATank; // Forward Delcaration
/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	//how close can the AI tank approach player
	UPROPERTY(EditAnywhere, Category = "Setup") //Consider EditDefaultsOnly
	float AcceptanceRadius = 8000;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	
};
