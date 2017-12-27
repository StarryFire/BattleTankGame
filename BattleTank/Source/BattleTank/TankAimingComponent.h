// Kartik TankGame Ltd.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

public:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 2000;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void MoveBarrel(FVector AimDirection);
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")  //For the corresponding Blueprint class of the C++ class to call this function, the function must be public/protected cuz the blueprint class is actually a subclass of the corresponding C++ class
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 3.0;

	double LastFireTime = 0;
};
