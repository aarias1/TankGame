// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"//Paste new includes above this
class UTankBarrel; // Forward Delcaration
class UTurret;
//class UTankAimingComponent;
//class AProjectile;
//class UTankMovementComponent;
UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	/*
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTurret* TurretToSet);
	*/

	

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	/*UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;*/

	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	
};
