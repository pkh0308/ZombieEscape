// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnHpChangedDelegate, float /*InHpRate*/);
DECLARE_DELEGATE_TwoParams(FOnMainAmmoChangedDelegate, int /*InCurAmmo*/, int /*RemainAmmo*/);
DECLARE_DELEGATE_OneParam(FOnSubAmmoChangedDelegate, int /*InCurAmmo*/);
DECLARE_DELEGATE_OneParam(FOnGrenadeChangedDelegate, int /*RemainGrenade*/);
DECLARE_DELEGATE_OneParam(FOnHealPackChangedDelegate, int /*RemainHealPack*/);

UENUM()
enum class EHandType : uint8
{
	None = 0,
	MainWeapon,
	SubWeapon,
	Grenade,
	HealPack
};

/**
 * 
 */

UCLASS()
class FPSTEST_API APlayerCharacter : public APlayerBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	class AMyPlayerController* GetMyController();

protected:
	UPROPERTY()
	TObjectPtr<class UCameraComponent> PlayerCamera;

// Input Action
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputMappingContext> PlayerMappingContext;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> ReloadAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> ZoomAction;

	// Hand Change
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToMainAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToSubAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToGrenadeAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HandChangeToHealPackAction;

	// Heal
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> HealAction;

	// Heal
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInputAction> MeleeAttackAction;


	void Move(const FInputActionValue& InputAction);
	void Look(const FInputActionValue& InputAction);
	void Attack(const FInputActionValue& InputAction);
	void AttackEnd(const FInputActionValue& InputAction);
	void Reload(const FInputActionValue& InputAction);

	void HandChangeToMain(const FInputActionValue& InputAction);
	void HandChangeToSub(const FInputActionValue& InputAction);
	void HandChangeToGrenade(const FInputActionValue& InputAction);
	void HandChangeToHealPack(const FInputActionValue& InputAction);

	void ZoomIn(const FInputActionValue& InputAction);
	void ZoomOut(const FInputActionValue& InputAction);

	void Heal(const FInputActionValue& InputAction);

	void MeleeAttack(const FInputActionValue& InputAction);

// Weapon
protected:
	UPROPERTY()
	TSubclassOf<class AMainWeapon> MainWeaponClass;

	UPROPERTY()
	TObjectPtr<class AMainWeapon> MainWeapon;

	UPROPERTY()
	TSubclassOf<class ASubWeapon> SubWeaponClass;

	UPROPERTY()
	TObjectPtr<class ASubWeapon> SubWeapon;

// Zombie Reference
protected:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class ACharacter> ZombieClass;


// HandType
protected:
	EHandType CurHand;

// Shoot & Reload
protected:
	UPROPERTY()
	TSubclassOf<class ABullet> BulletClass;

	FTimerHandle FireHandle;

	bool IsReloading = false;
	bool IsFiring = false;
	bool IsZooming = false;
	float FireDelayTime = 0.12f;
	float ReloadDelayTime = 1.5f;
	float MuzzleOffsetZ = 70.0f;

	float ZoomInFov = 60.0f;
	float ZoomOutFov = 90.0f;
	float MoveSpeedInZooming = 200.0f;
	float MoveSpeedInFiring = 350.0f;
	float MoveSpeedInNormal = 500.0f;

	float CurShootAccurancy = 1.0f;
	float MaxShootAccurancy = 1.0f;
	float DeltaShootAccurancy = 0.02f;
	float ShootAccurancyOffset = 10;

	int32 GetAttackPower();

	void OneShot();
	void Shoot();
	void StopShoot();
	void ReloadComplete();

// Recoil
protected:
	float RecoilOffsetInNormal = 0.4f;
	float RecoilOffsetInZoom = 0.2f;

// Grenade
protected:
	UPROPERTY()
	TSubclassOf<class AThrowableWeaponBase> GrenadeClass;

	bool IsThrowing = false; 
	float ThrowDelay = 1.5f;

	void ThrowGrenade();

// HealPack
protected:
	bool IsHealing = false;
	float HealDelayTime = 4.0f;
	int32 HealAmount = 30;

// Melee Attack
protected:
	FVector MeleeAttackBoxVec = FVector(50, 80, 35);
	FVector MeleeAttackMuzzleOffset = FVector(0, 0, 30);

	int32 MeleeAttackPower = 30;
	float KnuckbackPower = 800.0f;
	bool IsMeleeAttackDelay = false;
	float MeleeAttackDelay = 1.0f;

// Status
protected:
	UPROPERTY(EditAnywhere)
	int32 MaxHp = 100;

	UPROPERTY(EditAnywhere)
	int32 CurHp;

	UPROPERTY(EditAnywhere)
	int32 CurMainAmmo = 30;

	int32 MaxMainAmmo = 30;

	UPROPERTY(EditAnywhere)
	int32 RemainMainAmmo = 60;

	UPROPERTY(EditAnywhere)
	int32 CurSubAmmo = 12;

	int32 MaxSubAmmo = 12;

	UPROPERTY(EditAnywhere)
	int32 RemainGrenade = 3;

	UPROPERTY(EditAnywhere)
	int32 RemainHealPack = 1;

	bool IsDead = false;

public:
	UFUNCTION()
	int SetHp(int32 NewHp);

	void OnDie();

	UFUNCTION()
	int SetCurMainAmmo(int32 NewCurAmmo);

	UFUNCTION()
	int SetRemainMainAmmo(int32 NewRemainAmmo);

	UFUNCTION()
	int SetCurSubAmmo(int32 NewCurAmmo);

	UFUNCTION()
	int SetRemainGrenade(int32 NewRemainGrenade);

	UFUNCTION()
	int SetRemainHealPack(int32 NewRemainHealPack);

	UFUNCTION(BlueprintCallable)
	void OnDamaged(int32 InDamage);
	
// Delegate
public:
	FOnHpChangedDelegate OnHpChanged;
	FOnMainAmmoChangedDelegate OnMainAmmoChanged;
	FOnSubAmmoChangedDelegate OnSubAmmoChanged;
	FOnGrenadeChangedDelegate OnGrenadeChanged;
	FOnHealPackChangedDelegate OnHealPackChanged;

protected:
	void ShowProcessUI();

// Item
public:
	void GetItem(struct FItemData ItemData);

};
