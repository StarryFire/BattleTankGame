// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"            // .generated.h must be the last include

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();
	bool GetLookVectorHitLocation(FVector &HitLocation, FVector LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

private:
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
