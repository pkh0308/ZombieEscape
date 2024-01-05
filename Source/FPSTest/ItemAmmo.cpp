// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAmmo.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AItemAmmo::AItemAmmo()
{
	// Static Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
		Mesh->SetupAttachment(SphereComponent);
	}

	ItemData = FItemData(EItemType::Ammo, AmmoValue);
}
