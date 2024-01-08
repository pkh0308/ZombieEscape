// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieBase.generated.h"

UCLASS()
class FPSTEST_API AZombieBase : public ACharacter
{
	GENERATED_BODY()

public:
	AZombieBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


// Status
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower;

// Functions
public:
	UFUNCTION(BlueprintCallable)
	void OnDamaged(int32 InDamage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDie();

};
