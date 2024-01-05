// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemGrenade.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AItemGrenade::AItemGrenade()
{
	//Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
		Mesh->SetupAttachment(SphereComponent);
	}

	ItemData = FItemData(EItemType::Grenade, GrenadeCount);
}
