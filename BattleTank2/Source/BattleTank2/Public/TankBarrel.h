// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downward movement, +1 is max up movement
    void Elevate(float RelativeSpeed);
	
private:
    UPROPERTY(EditAnywhere, Category=Setup)
    float MaxDegreesPerSecond = 20;
    
    UPROPERTY(EditAnywhere, Category=Setup)
    float MaxElevationInDegrees = 40;
    
    UPROPERTY(EditAnywhere, Category=Setup)
    float MinElevationInDegrees = 0;
    
};
