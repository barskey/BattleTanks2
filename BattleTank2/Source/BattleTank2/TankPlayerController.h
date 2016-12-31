// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    ATank* GetControlledTank() const;

    UPROPERTY(EditAnywhere);
    float CrosshairXLocation = 0.5f;

    UPROPERTY(EditAnywhere);
    float CrosshairYLocation = 0.33333f;
    
    // start the tank moving the barrel so a shot will hit where crosshair aims
    void AimAtCrosshair();
    
    // return an OUT parameter, true if hits landscape
    bool GetSightRayHitLocation( FVector& HitLocation ) const;
};
