// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    auto ControlledTank = Cast<ATank>(GetPawn());
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if (!PlayerPawn) { return; }
    
    auto PlayerTank = Cast<ATank>(PlayerPawn);

    // TODO move towards player
    
    // TODO aim towards player
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    
    // TODO fire if ready
    ControlledTank->Fire();
    
}
