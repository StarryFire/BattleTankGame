// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	if( controlledTank == NULL )
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Not In Control Of Any Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller In Control Of %s"), *controlledTank->GetName());

	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return (ATank*)GetPawn();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == NULL)
		return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	FVector LookDirection;
	GetLookDirection(ScreenLocation, LookDirection);
	GetLookVectorHitLocation(HitLocation, LookDirection);

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *LookDirection.ToString());
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector LookDirection) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = LookDirection*LineTraceRange + StartLocation;
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
		return true;
	}
	else
		return false;
}





