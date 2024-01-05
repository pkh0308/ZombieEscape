// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEST_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UProgressBar> HpBarWidget;

public:
	UFUNCTION()
	void UpdateHpBar(float HpRate);

	void SetDelegate(class APlayerCharacter* PlayerCharacter);

};
