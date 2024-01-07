// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
protected:
	virtual void BeginPlay() override;

protected:
	// Hp Bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHpBarWidget> HpBarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UHpBarWidget> HpBar;

	// Ammo Count
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAmmoCountWidget> AmmoCountClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAmmoCountWidget> AmmoCount;

	// Crosshair
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCrosshairWidget> CrosshairClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCrosshairWidget> CrosshairWidget;

	// Process UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UProcessUIWidget> ProcessUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UProcessUIWidget> ProcessUIWidget;

	// GameOver UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameOverUIWidget> GameOverUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UGameOverUIWidget> GameOverUIWidget;


public:
	void InitWidget(class APlayerCharacter* InPlayerCharacter);

	void ShowProcessUI(FText Text, float Time);

	void GameOver();
};
