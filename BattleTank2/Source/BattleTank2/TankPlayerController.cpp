// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (AimingComponent) {
        FoundAimingComponent(AimingComponent);
    } else {
        UE_LOG(LogTemp, Error, TEXT("PlayerContorller can't find AimingComponent at BeginPlay"))
    }
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    AimAtCrosshair();
    
}

void ATankPlayerController::AimAtCrosshair()
{
    if (!GetPawn()) { return; } // e.g. Not possesing
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent) { return; }
    
    FVector HitLocation; // out parameter
    if (GetSightRayHitLocation(HitLocation)) {
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    // find the crosshair position in pixel coords
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    
    // "de-project" screen position of the crosshair to a world position
    FVector LookDirection;
    if (GetLookDirection( ScreenLocation, LookDirection )) {
        // linetrace along that look direction and see if we hit something (up to max range)
        GetLookDirectionHitLocation(LookDirection, HitLocation);
        
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookDirectionHitLocation( FVector LookDirection, FVector& HitLocation ) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
     HitResult,
     StartLocation,
     EndLocation,
     ECollisionChannel::ECC_Visibility)
    ) {
        HitLocation = HitResult.Location;
        return true;
    } else {
        HitLocation = FVector(0);
        return false;
    }
}
