// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last include
class UTankBarrel; // Forward Delcaration
class ATank;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//ATank* GetControlledTank() const;
	//Start the tank moving the barrel so that a ashot would hit where the crosshair is
	void AimTowardsCrosshair();
	
protected:
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitDirection) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	
};
