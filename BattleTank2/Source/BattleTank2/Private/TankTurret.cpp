// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
    // move turret the right amount this frame given a max move speed and the frame time
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = RelativeRotation.Yaw + RotationChange;
    
    SetRelativeRotation(FRotator(0, NewRotation, 0));
}
