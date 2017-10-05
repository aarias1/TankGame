// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	//Start the tank moving the barrel so that a ashot would hit where the crosshair is
	void AimTowardsCrosshair();
protected:
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
