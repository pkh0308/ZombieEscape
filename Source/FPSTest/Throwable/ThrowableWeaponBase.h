// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableWeaponBase.generated.h"

UCLASS()
class FPSTEST_API AThrowableWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowableWeaponBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystemComponent> ParticleComponent;

	float ExplodeDelay = 3.0f;
	float ExplodeRadius = 300.0f;

public:
	void Throw(FVector DirectionVec);

	UFUNCTION()
	void Explode();
};
