// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
	// Collision
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlap);
	SphereComponent->SetSphereRadius(10.0f);
}

void AItemBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->GetItem(ItemData);
		Destroy();
	}
}


