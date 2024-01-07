// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FPSTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	UPROPERTY(EditAnywhere)
	int32 AttackPower;

// Getter & Setter
public:
	FORCEINLINE void SetAttackPower(int32 NewAttackPower) { AttackPower = NewAttackPower; }
	FORCEINLINE int32 GetAttackPower() const { return AttackPower; }

};
