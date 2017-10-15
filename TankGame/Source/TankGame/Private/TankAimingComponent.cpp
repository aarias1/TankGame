// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // TODO should this really tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();

	//so that first fire is after reload
	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("TickComponent"));
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		//UE_LOG(LogTemp, Warning, TEXT("Reloading"));
		FiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving()) {
		//UE_LOG(LogTemp, Warning, TEXT("BarrelMoving"));
		FiringState = EFiringState::Aiming;
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Locked"));
		FiringState = EFiringState::Locked;
	}
	//TODO handle aiming and locked states
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

/*
void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}
*/

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!Barrel) { UE_LOG(LogTemp, Warning, TEXT("Np Barrel")); return; }
	if (!Turret) { UE_LOG(LogTemp, Warning, TEXT("No Turret")); return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // comment this line to produce this bug
	);
	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found"), Time);
		//auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s is Aiming at %s"), *TankName, *AimDirection.ToString());
	}
	

	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s at speed %f"), *OurTankName, *HitLocation.ToString(), *BarrelLocation, LaunchSpeed);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//Work out the difference between current barrel rotation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	//move the barrel the right amount this frame
	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic number
	Turret->Rotate(DeltaRotator.Yaw);
	//Turret->Rotate(1);
	//given a max elevation speed, and the frame time
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection,0.01);
}

void UTankAimingComponent::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("FIRE"));
	if (FiringState != EFiringState::Reloading) {
		//bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
		//if (isReloaded) {
			//Spawn projectile at the socket location
			if (!ensure(Barrel)) { return; }
			if (!ensure(ProjectileBlueprint)) { return; }
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")));

			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		//}
	}
}

