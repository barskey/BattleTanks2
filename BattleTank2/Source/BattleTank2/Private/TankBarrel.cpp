// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
    // move barrel the right amount this frame given a max move speed and the frame time
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto NewElevation = FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);
    
    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
