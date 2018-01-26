// Kartik TankGame Ltd.

#include "BattleTank.h"
#include "Tank.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")); 
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("DAMAGE TAKEN: %f"), DamageAmount);
	FPlatformMath::RoundToDouble(DamageAmount);
	auto DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("DAMAGE APPLIED: %d TANK HEALTH %d"), DamageToApply, CurrentHealth);
	return DamageAmount;
}