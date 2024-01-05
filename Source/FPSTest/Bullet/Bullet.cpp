// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	SphereComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));
	RootComponent = SphereComponent;

	// Projectile Component
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->SetUpdatedComponent(SphereComponent);
	ProjectileComponent->InitialSpeed = 5000.0f;
	ProjectileComponent->MaxSpeed = 5000.0f;
	ProjectileComponent->ProjectileGravityScale = 0;
	ProjectileComponent->bShouldBounce = false;

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}
	Mesh->SetupAttachment(SphereComponent);
	Mesh->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->Velocity = FVector::Zero();
}

void ABullet::Fire(FVector DirectionVec)
{
	ProjectileComponent->Velocity = DirectionVec * ProjectileComponent->InitialSpeed;
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// when zombie hit


	Destroy();
}

