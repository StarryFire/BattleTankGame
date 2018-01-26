// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnTimerExpire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

	UProjectileMovementComponent *ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ProjectileDamage = 20.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float DestroyDelay = 2.0f;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent *CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent *LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent *ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		URadialForceComponent *ExplosionForce = nullptr;
};
