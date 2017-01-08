// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeinSec) {
        FiringState = EFiringState::Reloading;
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    } else {
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!Barrel) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));
    
    // calculate the launch velocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );
    if (bHaveAimSolution) {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveTowards(FVector AimDirection)
{
    if (!Barrel || !Turret) { return; }

    // work out difference between current barrel rotation and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimRotator = AimDirection.Rotation();
    auto DeltaRotator = AimRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    if (DeltaRotator.Yaw < 180) {
        Turret->Rotate(DeltaRotator.Yaw);
    } else {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

void UTankAimingComponent::Fire()
{
    if (!Barrel || !ProjectileBlueprint) { return; }
    
        if (FiringState != EFiringState::Reloading) {
        // spawn a projectile at the socket location on the barrel
        auto Location = Barrel->GetSocketLocation(FName("ProjectileStart"));
        auto Rotation = Barrel->GetSocketRotation(FName("ProjectileStart"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!Barrel) { return false; }
    
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, 0.1f);
}
