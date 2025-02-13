// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEST_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCrosshairWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UImage> CrosshairImg;
	
};
