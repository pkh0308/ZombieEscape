// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/MyPlayerController.h"
#include "Bullet/Bullet.h"
#include "Components/CapsuleComponent.h"
#include "Item/ItemBase.h"
#include "Throwable/ThrowableWeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	// Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->AddRelativeLocation(FVector(20, 0, 70));
	PlayerCamera->bUsePawnControlRotation = true;

	// InputMapping
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PKH/Input/IMC_FPS.IMC_FPS'"));
	if (MappingContextRef.Object)
	{
		PlayerMappingContext = MappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Move.IA_FPS_Move'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Jump.IA_FPS_Jump'"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Look.IA_FPS_Look'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Attack.IA_FPS_Attack'"));
	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> ReloadActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Reload.IA_FPS_Reload'"));
	if (ReloadActionRef.Object)
	{
		ReloadAction = ReloadActionRef.Object;
	}
	// Hand Change
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToMainActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToMain.IA_FPS_HandChangeToMain'"));
	if (HandChangeToMainActionRef.Object)
	{
		HandChangeToMainAction = HandChangeToMainActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToSubActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToSub.IA_FPS_HandChangeToSub'"));
	if (HandChangeToSubActionRef.Object)
	{
		HandChangeToSubAction = HandChangeToSubActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToGrenadeActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToGrenade.IA_FPS_HandChangeToGrenade'"));
	if (HandChangeToGrenadeActionRef.Object)
	{
		HandChangeToGrenadeAction = HandChangeToGrenadeActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> HandChangeToHealPackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_HandChangeToHealPack.IA_FPS_HandChangeToHealPack'"));
	if (HandChangeToHealPackActionRef.Object)
	{
		HandChangeToHealPackAction = HandChangeToHealPackActionRef.Object;
	}
	// Zoom In/Out
	static ConstructorHelpers::FObjectFinder<UInputAction> ZoomActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Zoom.IA_FPS_Zoom'"));
	if (ZoomActionRef.Object)
	{
		ZoomAction = ZoomActionRef.Object;
	}
	// Heal
	static ConstructorHelpers::FObjectFinder<UInputAction> HealActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_Heal.IA_FPS_Heal'"));
	if (HealActionRef.Object)
	{
		HealAction = HealActionRef.Object;
	}
	// MeleeAttack
	static ConstructorHelpers::FObjectFinder<UInputAction> MeleeAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PKH/Input/IA_FPS_MeleeAttack.IA_FPS_MeleeAttack'"));
	if (MeleeAttackActionRef.Object)
	{
		MeleeAttackAction = MeleeAttackActionRef.Object;
	}

	// Bullet
	static ConstructorHelpers::FClassFinder<ABullet> BulletRef(TEXT("/Game/PKH/BP/BP_Bullet.BP_Bullet_C"));
	if (BulletRef.Class)
	{
		BulletClass = BulletRef.Class;
	}

	//Grenade
	static ConstructorHelpers::FClassFinder<AThrowableWeaponBase> GrenadeRef(TEXT("/Game/PKH/BP/BP_Grenade.BP_Grenade_C"));
	if (GrenadeRef.Class)
	{
		GrenadeClass = GrenadeRef.Class;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputCompoennt = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputCompoennt->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputCompoennt->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputCompoennt->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	EnhancedInputCompoennt->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	EnhancedInputCompoennt->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
	EnhancedInputCompoennt->BindAction(AttackAction, ETriggerEvent::Completed, this, &APlayerCharacter::AttackEnd);
	EnhancedInputCompoennt->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);
	// HandChange
	EnhancedInputCompoennt->BindAction(HandChangeToMainAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToMain);
	EnhancedInputCompoennt->BindAction(HandChangeToSubAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToSub);
	EnhancedInputCompoennt->BindAction(HandChangeToGrenadeAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToGrenade);
	EnhancedInputCompoennt->BindAction(HandChangeToHealPackAction, ETriggerEvent::Started, this, &APlayerCharacter::HandChangeToHealPack);
	// Zoom In/Out
	EnhancedInputCompoennt->BindAction(ZoomAction, ETriggerEvent::Started, this, &APlayerCharacter::ZoomIn);
	EnhancedInputCompoennt->BindAction(ZoomAction, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomOut);
	// Heal 
	EnhancedInputCompoennt->BindAction(HealAction, ETriggerEvent::Started, this, &APlayerCharacter::Heal);
	// MeleeAttack
	EnhancedInputCompoennt->BindAction(MeleeAttackAction, ETriggerEvent::Started, this, &APlayerCharacter::MeleeAttack);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Mapping
	AMyPlayerController* PlayerController = CastChecked<AMyPlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}

	PlayerController->InitWidget(this);

	// Status Init
	SetHp(MaxHp / 2);
	SetCurMainAmmo(MaxMainAmmo);
	SetCurSubAmmo(MaxSubAmmo);

	CurHand = EHandType::MainWeapon;
}

AMyPlayerController* APlayerCharacter::GetMyController()
{
	AMyPlayerController* MyController = CastChecked<AMyPlayerController>(GetController());
	return MyController;
}

void APlayerCharacter::Move(const FInputActionValue& InputAction)
{
	FVector2D InputVec = InputAction.Get<FVector2D>();

	const FRotator Rotator = Controller->GetControlRotation();
	const FRotator YawRotator = FRotator(0, Rotator.Yaw, 0);

	const FVector ForwardVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightVec = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVec, InputVec.Y);
	AddMovementInput(RightVec, InputVec.X);
}

void APlayerCharacter::Look(const FInputActionValue& InputAction)
{
	if (IsDead)
	{
		return;
	}

	FVector2D InputVec = InputAction.Get<FVector2D>();

	AddControllerPitchInput(InputVec.Y);
	AddControllerYawInput(InputVec.X);
}

void APlayerCharacter::Attack(const FInputActionValue& InputAction)
{
	if (IsMeleeAttackDelay || IsDead)
	{
		return;
	}

	switch (CurHand)
	{
	case EHandType::MainWeapon:
		Shoot();
		break;
	case EHandType::SubWeapon:
		OneShot();
		break;
	case EHandType::Grenade:
		ThrowGrenade();
		break;
	case EHandType::HealPack:

		break;
	}
}

void APlayerCharacter::AttackEnd(const FInputActionValue& InputAction)
{
	if (IsDead)
	{
		return;
	}
	if (CurHand != EHandType::MainWeapon)
	{
		return;
	}

	IsFiring = false;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeedInNormal;
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

void APlayerCharacter::Reload(const FInputActionValue& InputAction)
{
	if (IsReloading || IsFiring || IsDead)
	{
		return;
	}
	if (CurHand != EHandType::MainWeapon && CurHand != EHandType::SubWeapon)
	{
		return;
	}
	if (CurHand == EHandType::MainWeapon && (CurMainAmmo == MaxMainAmmo || RemainMainAmmo == 0))
	{
		return;
	}
	if (CurHand == EHandType::SubWeapon && CurSubAmmo == MaxSubAmmo)
	{
		return;
	}

	IsReloading = true;
	ShowProcessUI();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &APlayerCharacter::ReloadComplete, ReloadDelayTime, false);
	UE_LOG(LogTemp, Log, TEXT("Reload"));
}

void APlayerCharacter::HandChangeToMain(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::MainWeapon)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	CurHand = EHandType::MainWeapon;
}

void APlayerCharacter::HandChangeToSub(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::SubWeapon)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::SubWeapon;
}

void APlayerCharacter::HandChangeToGrenade(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::Grenade)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::Grenade;
}

void APlayerCharacter::HandChangeToHealPack(const FInputActionValue& InputAction)
{
	if (CurHand == EHandType::HealPack)
	{
		return;
	}
	if (IsHealing || IsDead)
	{
		return;
	}

	ZoomOut(FInputActionValue());
	CurHand = EHandType::HealPack;
}

void APlayerCharacter::ZoomIn(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::MainWeapon)
	{
		return;
	}
	if(IsDead)
	{
		return;
	}

	IsZooming = true;
	PlayerCamera->FieldOfView = ZoomInFov;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeedInZooming;
}

void APlayerCharacter::ZoomOut(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::MainWeapon)
	{
		return;
	}
	if (IsDead)
	{
		return;
	}

	IsZooming = false;
	PlayerCamera->FieldOfView = ZoomOutFov;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeedInNormal;
}

void APlayerCharacter::Heal(const FInputActionValue& InputAction)
{
	if (CurHand != EHandType::HealPack || IsHealing || IsDead)
	{
		return;
	}
	if (RemainHealPack < 1)
	{
		return;
	}

	IsHealing = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetRemainHealPack(RemainHealPack - 1);
	ShowProcessUI();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			SetHp(CurHp + HealAmount);
			IsHealing = false;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}), HealDelayTime, false);
}

void APlayerCharacter::MeleeAttack(const FInputActionValue& InputAction)
{
	if (IsMeleeAttackDelay || IsDead)
	{
		return;
	}
	IsMeleeAttackDelay = true;

	if (IsFiring)
	{
		StopShoot();
	}

	const FVector ForwardVec = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X);
	FVector AttackCenterVec = GetActorLocation() + MeleeAttackMuzzleOffset + ForwardVec * GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 3.0f;
	
	TArray<FOverlapResult> OverlapResults;
	bool IsHitted = GetWorld()->OverlapMultiByChannel(OverlapResults, AttackCenterVec, FQuat::MakeFromRotator(GetController()->GetControlRotation()),
													  ECollisionChannel::ECC_GameTraceChannel14, FCollisionShape::MakeBox(MeleeAttackBoxVec));

	if (IsHitted)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			ACharacter* HittedCharacter = Cast<ACharacter>(OverlapResults[i].GetActor());
			if (HittedCharacter)
			{
				FVector MyLocation = GetActorLocation();
				MyLocation.Z = 0;
				FVector TargetLocation = HittedCharacter->GetActorLocation();
				TargetLocation.Z = 0;
				FVector DirectionVec = TargetLocation - MyLocation;
				DirectionVec.Normalize();
				HittedCharacter->LaunchCharacter(DirectionVec * KnuckbackPower, true, false);
				
				//DrawDebugBox(GetWorld(), AttackCenterVec, MeleeAttackBoxVec, FColor::Green, false, 0.5f);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack Hit: %d"), MeleeAttackPower);
			}
		}
	}
	else
	{
		//DrawDebugBox(GetWorld(), AttackCenterVec, MeleeAttackBoxVec, FColor::Red, false, 0.5f);
	}

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			IsMeleeAttackDelay = false;
		}), MeleeAttackDelay, false);
}

int APlayerCharacter::SetHp(int32 NewHp)
{
	CurHp = FMath::Clamp(NewHp, 0, MaxHp);
	OnHpChanged.ExecuteIfBound((float)CurHp / MaxHp);
	if (CurHp == 0)
	{
		OnDie();
	}

	return CurHp;
}

int APlayerCharacter::SetCurMainAmmo(int32 NewCurAmmo)
{
	CurMainAmmo = FMath::Clamp(NewCurAmmo, 0, MaxMainAmmo);
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, RemainMainAmmo);

	if (CurMainAmmo == 0)
	{
		StopShoot();
	}

	return CurMainAmmo;
}

int APlayerCharacter::SetRemainMainAmmo(int32 NewRemainAmmo)
{
	RemainMainAmmo = FMath::Clamp(NewRemainAmmo, 0, 500); // 500 is temp
	OnMainAmmoChanged.ExecuteIfBound(CurMainAmmo, RemainMainAmmo);

	return RemainMainAmmo;
}

int APlayerCharacter::SetCurSubAmmo(int32 NewCurAmmo)
{
	CurSubAmmo = FMath::Clamp(NewCurAmmo, 0, MaxSubAmmo);
	OnSubAmmoChanged.ExecuteIfBound(CurSubAmmo);

	return CurSubAmmo;
}

int APlayerCharacter::SetRemainGrenade(int32 NewRemainGrenade)
{
	RemainGrenade = FMath::Clamp(NewRemainGrenade, 0, 500); // 500 is temp
	OnGrenadeChanged.ExecuteIfBound(RemainGrenade);

	return RemainGrenade;
}

int APlayerCharacter::SetRemainHealPack(int32 NewRemainHealPack)
{
	RemainHealPack = FMath::Clamp(NewRemainHealPack, 0, 500); // 500 is temp
	OnHealPackChanged.ExecuteIfBound(RemainHealPack);

	return RemainHealPack;
}

void APlayerCharacter::OnDamaged(int32 InDamage)
{
	SetHp(CurHp - InDamage);
	UE_LOG(LogTemp, Log, TEXT("OnDamaged: %d"), InDamage);
}

void APlayerCharacter::OnDie()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	IsDead = true;

	// Animation


	// GameOver UI
	GetMyController()->GameOver();
}

void APlayerCharacter::ShowProcessUI()
{
	if (IsReloading)
	{
		GetMyController()->ShowProcessUI(FText::FromString(TEXT("Reloading...")), ReloadDelayTime);
	}
	else if (IsHealing)
	{
		GetMyController()->ShowProcessUI(FText::FromString(TEXT("Healing...")), HealDelayTime);
	}
}

void APlayerCharacter::GetItem(FItemData ItemData)
{
	switch (ItemData.ItemType)
	{
	case EItemType::Heal:
		SetRemainHealPack(RemainHealPack + ItemData.ItemValue);
		break;
	case EItemType::Ammo:
		SetRemainMainAmmo(RemainMainAmmo + ItemData.ItemValue);
		break;
	case EItemType::Grenade:
		SetRemainGrenade(RemainGrenade + ItemData.ItemValue);
		break;
	}
}

int32 APlayerCharacter::GetAttackPower()
{
	if (CurHand == EHandType::MainWeapon)
	{
		return 30;
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		return 15;
	}

	return 0;
}

void APlayerCharacter::OneShot()
{
	if (CurHand == EHandType::MainWeapon && CurMainAmmo < 1)
	{
		return;
	}
	if (CurHand == EHandType::SubWeapon && CurSubAmmo < 1)
	{
		return;
	}

	const FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, MuzzleOffsetYaw) + (GetActorForwardVector() * (GetCapsuleComponent()->GetUnscaledCapsuleRadius()));
	const FRotator MuzzleRotator = FRotationMatrix::MakeFromX(GetActorForwardVector()).Rotator();

	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FVector ControllerForwardVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::X);

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, MuzzleLocation, MuzzleRotator, Params);
	if (Projectile)
	{
		Projectile->Fire(ControllerForwardVec, GetAttackPower());
	}

	if (CurHand == EHandType::MainWeapon)
	{
		SetCurMainAmmo(CurMainAmmo - 1);;
	}
	else
	{
		SetCurSubAmmo(CurSubAmmo - 1);;
	}
}

void APlayerCharacter::Shoot()
{
	if (IsReloading)
	{
		return;
	}

	if (false == IsFiring)
	{
		OneShot();

		IsFiring = true;
		if (IsZooming == false)
		{
			GetCharacterMovement()->MaxWalkSpeed = MoveSpeedInFiring;
		}
		
		if (!FireHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(FireHandle,
				FTimerDelegate::CreateLambda([this]()
					{
						OneShot();
						// Fire Start
						if (CurMainAmmo < 1)
						{
							this->IsFiring = false;
							GetWorld()->GetTimerManager().ClearTimer(FireHandle);
						}
					}), FireDelayTime, true);
		}
	}
}

void APlayerCharacter::StopShoot()
{
	if (IsZooming == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeedInNormal;
	}
	if (FireHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FireHandle);
	}
}

void APlayerCharacter::ReloadComplete()
{
	if (CurHand == EHandType::MainWeapon)
	{
		int32 diff = MaxMainAmmo - CurMainAmmo;
		if (diff >= RemainMainAmmo)
		{
			SetCurMainAmmo(CurMainAmmo + RemainMainAmmo);
			SetRemainMainAmmo(0);
		}
		else
		{
			SetCurMainAmmo(MaxMainAmmo);
			SetRemainMainAmmo(RemainMainAmmo - diff);
		}
	}
	else if (CurHand == EHandType::SubWeapon)
	{
		SetCurSubAmmo(MaxSubAmmo);
	}
	IsReloading = false;

	UE_LOG(LogTemp, Log, TEXT("%d / %d"), CurMainAmmo, RemainMainAmmo);
}

void APlayerCharacter::ThrowGrenade()
{
	if (RemainGrenade < 1 || IsThrowing)
	{
		return;
	}
	IsThrowing = true;

	const FVector MuzzleLocation = GetActorLocation() + FVector(0, 0, MuzzleOffsetYaw) + (GetActorForwardVector() * (GetCapsuleComponent()->GetUnscaledCapsuleRadius()));
	const FRotator MuzzleRotator = FRotationMatrix::MakeFromX(GetActorForwardVector()).Rotator();

	const FRotator ControllerRotator = Controller->GetControlRotation();
	const FVector ControllerForwardVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::X);
	const FVector ControllerUpVec = FRotationMatrix(ControllerRotator).GetUnitAxis(EAxis::Z) * 0.2f;
	FVector ThrowDirVec = (ControllerForwardVec + ControllerUpVec);
	ThrowDirVec.Normalize();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	AThrowableWeaponBase* Throwable = GetWorld()->SpawnActor<AThrowableWeaponBase>(GrenadeClass, MuzzleLocation, MuzzleRotator, Params);
	if (Throwable)
	{
		Throwable->Throw(ThrowDirVec);
	}
	SetRemainGrenade(RemainGrenade - 1);
	UE_LOG(LogTemp, Log, TEXT("Grenade: %d"), RemainGrenade);

	// Timer
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,
		[&]()
		{
			IsThrowing = false;
		}, 1.0f, false, ThrowDelay);
}
