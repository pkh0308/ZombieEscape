// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Zombie/ZombieBase.h"

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
	ProjectileComponent->InitialSpeed = 10000.0f;
	ProjectileComponent->MaxSpeed = 10000.0f;
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

void ABullet::Fire(FVector DirectionVec, int32 NewAttackPower)
{
	ProjectileComponent->Velocity = DirectionVec * ProjectileComponent->InitialSpeed;
	AttackPower = NewAttackPower;
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// when zombie hit
	AZombieBase* Zombie = Cast<AZombieBase>(OtherActor);
	if (Zombie)
	{
		Zombie->OnDamaged(AttackPower);
		UE_LOG(LogTemp, Log, TEXT("Bullet Hit: %d"), AttackPower);
	}

	Destroy();
}

