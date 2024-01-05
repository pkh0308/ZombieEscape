// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ProcessUIWidget.h"
#include "Components/TextBlock.h"

UProcessUIWidget::UProcessUIWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProcessUIWidget::NativeConstruct()
{
	ProcessText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ProcessText")));
	ensure(ProcessText);
}

void UProcessUIWidget::SetProcessData(FText Text, float Time)
{
	ProcessText->SetText(Text);
}
