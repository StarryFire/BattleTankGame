// Kartik TankGame Ltd.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw %f"), Throw);
	if (!LeftTrack || !RightTrack)
		return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)   //turns right with +ve throw
{
	if (!LeftTrack || !RightTrack)
		return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto AIThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto AIRightTurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention);  //Order of arguments matter here ! 
	
	IntendTurn(AIRightTurnThrow.Z);
	IntendMoveForward(AIThrow);
	
	//UE_LOG(LogTemp, Warning, TEXT("%s with move velocity %s"),*TankForward.ToString(),*AIForwardIntention.ToString());
}



