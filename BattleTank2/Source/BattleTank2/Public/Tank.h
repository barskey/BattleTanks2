// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be last

UCLASS()
class BATTLETANK2_API ATank : public APawn
{
	GENERATED_BODY()
    
private:
	// Sets default values for this pawn's properties
	ATank();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    int32 MaxHealth = 200;
    
private:
    UPROPERTY(VisibleAnywhere, Category="Setup")
    int32 CurrentHealth = 0;
};
