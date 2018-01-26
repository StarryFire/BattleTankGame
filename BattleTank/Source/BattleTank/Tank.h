// Kartik TankGame Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = MaxHealth;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	ATank();
};