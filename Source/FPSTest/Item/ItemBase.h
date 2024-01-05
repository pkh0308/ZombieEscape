// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UENUM()
enum class EItemType: uint8
{
	None = 0,
	Heal,
	Ammo,
	Grenade
};

USTRUCT()
struct FItemData
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() : ItemType(EItemType::None), ItemValue(0) {}
	FItemData(EItemType Type, int32 Value) : ItemType(Type), ItemValue(Value) {}

	EItemType ItemType;
	int32 ItemValue;
};

UCLASS()
class FPSTEST_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	FItemData ItemData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
