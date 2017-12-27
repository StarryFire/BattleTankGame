// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ensure(GetPawn()))
		return;

	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(TankAimingComponent))
		FoundAimingComponent(TankAimingComponent);
}


/*
UNREAL BUG : If a blueprint has any functionality on tick, the tick event will fire when a blueprint is restored within the editor after closing and reopening a project.
IMPLICATION : When opening TankPlayerController_BP to edit in editor,it will call Tick function of TankPlayerController 
*/
void ATankPlayerController::Tick(float DeltaTime)       
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn()))   //There will be no pawn when editing the Blueprint and thus this will return nullptr and then the next line of code will cause the editor to crash
		return;
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
		return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		TankAimingComponent->AimAt(HitLocation);
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
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
		return true;
	}
	else
		return false;
}





