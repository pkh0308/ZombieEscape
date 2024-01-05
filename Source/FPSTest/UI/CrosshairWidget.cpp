// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CrosshairWidget.h"
#include "CrosshairWidget.h"
#include "Components/Image.h"

UCrosshairWidget::UCrosshairWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCrosshairWidget::NativeConstruct()
{
	CrosshairImg = Cast<UImage>(GetWidgetFromName(TEXT("Crosshair")));
	ensure(CrosshairImg);
}
