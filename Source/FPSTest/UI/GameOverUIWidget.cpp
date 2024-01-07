// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverUIWidget.h"
#include "Components/TextBlock.h"

UGameOverUIWidget::UGameOverUIWidget(const FObjectInitializer& ObjectInitilaizer) : Super(ObjectInitilaizer)
{
}

void UGameOverUIWidget::NativeConstruct()
{
	GameOverText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GameOverText")));
	ensure(GameOverText);

	AnnouncementText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AnnouncementText")));
	ensure(AnnouncementText);
}
