// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/HeadUpWidgetComponent.h"
#include "HUD/Combat/HeadUpWidget.h"
#include "HUD/Combat/HeadUpText.h"

void UHeadUpWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	UHeadUpWidget* HeadUpWidget = Cast<UHeadUpWidget>(GetUserWidgetObject());
	if (HeadUpWidget)
	{
		this->SetWidgetSpace(EWidgetSpace::Screen);
	}
}