// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s."), *(ControlledTank->GetName()));
    }
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    AimAtCrosshair();
    
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
    if (!GetControlledTank()) { return; }
    
    FVector HitLocation; // out parameter
    if (GetSightRayHitLocation(HitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // TODO tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    HitLocation = FVector(1.f);
    return true;
}
