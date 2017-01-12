// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankAimingComponent.h"
#include "Tank.h" // so we can implement on death
#include "TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if (InPawn) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) { return; }
    
        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
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
    
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
        AimingComponent->Fire();
    }
}
