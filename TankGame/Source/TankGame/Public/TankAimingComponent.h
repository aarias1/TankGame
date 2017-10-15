// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Delcaration
class UTankBarrel; 
class UTurret;
class AProjectile;
//Holds parameters for barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();
	//void SetBarrelReference(UTankBarrel* BarrelToSet);

	//turret rotation
	//void SetTurretReference(UTurret* TurretToSet);


	//TODO add set turret reference

	//void AimAt(FVector HitLocation, float LaunchSpeed);
	void AimAt(FVector HitLocation);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// Sets default values for this component's properties
	UTankAimingComponent();
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	bool isBarrelMoving();
		
	FVector AimDirection;
	
};
