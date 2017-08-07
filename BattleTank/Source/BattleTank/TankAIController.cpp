// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return (ATank*)GetPawn();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	if (controlledTank == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Not In Control Of Any Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller In Control Of %s"), *controlledTank->GetName());
	}

	ATank* PlayerTank = GetPlayerTank();

	if (PlayerTank == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Did Not Find Any Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found Player Tank : %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = (ATank*)GetWorld()->GetFirstPlayerController()->GetPawn();

	return PlayerTank;
}

