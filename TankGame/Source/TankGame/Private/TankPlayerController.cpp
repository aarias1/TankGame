// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
//#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	if (!GetPawn()) { return; }
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	
	/*
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}*/
}
//Tick
	//Super
	
	// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("tick"))
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has a side effect, is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
		
		// TODO tell controlled tank to aim at this point
	}

	//Get world location if linetrace through crosshair

	//if it hits the landscape

	//tell controlled tank to aim at this point
}

/*pass by reference. Passing a reference to an FVector
* Get world location of linetrace through crosshair, true if hits landscape
* Create Hitlocation, pass the reference to hitlocation, and change the value of hitlocation
*/
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation:  %s"), *ScreenLocation.ToString());

	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation:  %s"), *LookDirection.ToString());
		//Line-trace along that look direction, and see what we hit
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility)) 
	{
		//Set hit location
		HitDirection = HitResult.Location;
		return true;
	}
	HitDirection = FVector(0);
	return false;
}

/*ATank* ATankPlayerController::GetControlledTank() const {
	return GetPawn();
}*/


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector WorldLoc;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLoc,
		LookDirection);
}

