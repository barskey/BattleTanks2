// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
    // Get unit vector in direction the tank is facing
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    // Get unit vector in direction Tank intends to move
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    
    auto MoveThrow = FVector::DotProduct(TankForward, AIForwardIntention); // returns float between -1 and 1
    IntendMoveForward(MoveThrow);

    // Cross Product returns vector, so use z component to determine throw
    auto TurnThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
    IntendTurn(TurnThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
