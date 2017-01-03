// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // no need to protect pointers as they are added in construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("FIRE!"))
    
    if (!Barrel) {
        UE_LOG(LogTemp, Error, TEXT("Barrel local reference not set in Tank.cpp"))
        return;
    }
    // spawn a projectile at the socket location on the barrel
    auto Location = Barrel->GetSocketLocation(FName("ProjectileStart"));
    auto Rotation = Barrel->GetSocketRotation(FName("ProjectileStart"));
    GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
}
