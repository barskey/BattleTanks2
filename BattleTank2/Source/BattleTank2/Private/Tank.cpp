// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay to run!
    
    CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0.f, CurrentHealth);
    CurrentHealth -= DamageToApply;
    UE_LOG(LogTemp, Warning, TEXT("HIT! Damage Amount: %i, New Current Health: %i"), DamageToApply, CurrentHealth)

    return DamageToApply;
}
