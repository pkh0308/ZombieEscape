// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class FPSTEST_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	float BulletLifeTime = 3.0f;

public:
	void Fire(FVector DirectionVec);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
