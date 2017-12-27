// Kartik TankGame Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(GetPawn()))
		return;
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();            //TODO Protect pointers returned by GetWorld() and GetFirstPlayerController()

	if (!ensure(PlayerTank && TankAimingComponent))
		return;
	
	MoveToActor(PlayerTank, AcceptanceRadius);
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	TankAimingComponent->Fire();
}