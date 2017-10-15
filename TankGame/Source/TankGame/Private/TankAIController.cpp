// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
//#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radiusis in cm
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		//TODO fix firing
		AimingComponent->Fire(); //TODO limit fire rate
}




