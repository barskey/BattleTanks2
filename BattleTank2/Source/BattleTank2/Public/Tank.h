// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be last

// forward declarations
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category="Firing")
    void Fire();

protected:
    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;
    
private:
	// Sets default values for this pawn's properties
	ATank();

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float LaunchSpeed = 100000; // TODO figure out reasonable starting value
    
    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float ReloadTimeinSec = 3;
    
    double LastFireTime = 0;

};
