// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    //auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("Intend move forward Throw: %f"), Throw)

}

