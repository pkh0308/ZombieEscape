// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProcessUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEST_API UProcessUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UProcessUIWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ProcessText;

public:
	void SetProcessData(FText Text, float Time);
};
