// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    // Get the aiming component of the controlled tank.  GetPawn returns the Controlled Tank
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!AimingComponent || !PlayerTank) { return; }
    
    // Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    // aim towards player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    // TODO fire if ready
    // ControlledTank->Fire();
}
