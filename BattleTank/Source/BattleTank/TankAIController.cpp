// Kartik TankGame Ltd.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = (ATank*)GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* ControlledTank = (ATank*)GetPawn();

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}