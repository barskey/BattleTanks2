// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    UE_LOG(LogTemp, Warning, TEXT("MYPREFIX: Tank.cpp Constructor."))
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to run!
	UE_LOG(LogTemp, Warning, TEXT("MYPREFIX: Tank.cpp BeginPlay."))
}

void ATank::AimAt(FVector HitLocation)
{
    if (!TankAimingComponent) { return; }
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeinSec;
    if (Barrel && isReloaded) {
        // spawn a projectile at the socket location on the barrel
        auto Location = Barrel->GetSocketLocation(FName("ProjectileStart"));
        auto Rotation = Barrel->GetSocketRotation(FName("ProjectileStart"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}
