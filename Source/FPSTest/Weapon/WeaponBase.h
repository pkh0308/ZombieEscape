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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower = 0;

public:
	FORCEINLINE int32 GetAttackPower() const { return AttackPower; }

};
