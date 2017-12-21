// Kartik TankGame Ltd.
#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;
};
