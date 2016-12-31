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
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
        // TODO tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    // find the crosshair position in pixel coords
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D( ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    
    // "de-project" screen position of the crosshair to a world position
    // linetrace along that look direction and see if we hit something (up to max range)
    return true;
}
