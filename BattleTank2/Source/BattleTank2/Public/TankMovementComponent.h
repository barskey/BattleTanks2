// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category="Setup")
    void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
    
    UFUNCTION(BlueprintCallable, Category="Input")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category="Input")
    void IntendTurn(float Throw);
    
private:
    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;

    // called from the pathfinding logic by the AI contorllers
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
