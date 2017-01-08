// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
    UTankTrack();
    
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void ApplyLateralForce();
    
    void DriveTrack();
    
    float CurrentThrottle = 0;

public:
    UFUNCTION(BlueprintCallable, Category="Input")
    void SetThrottle(float Throttle);
    
    // max force per track in Newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 200000; // assume 40K kg tank and 1g accel
};
