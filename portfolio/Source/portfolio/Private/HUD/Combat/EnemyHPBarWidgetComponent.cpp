// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/EnemyHPBarWidgetComponent.h"
#include "HUD/Combat/EnemyHPBarWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHPBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	HPBarWidget = Cast<UEnemyHPBarWidget>(GetUserWidgetObject());
}

void UEnemyHPBarWidgetComponent::SetHPBar(float Percent)
{
	if (HPBarWidget)
	{
		HPBarWidget->HPBar->SetPercent(Percent);
	}
}

float UEnemyHPBarWidgetComponent::GetHPBar() const
{
	if (HPBarWidget)
	{
		 return HPBarWidget->HPBar->GetPercent();
	}
	return 0.0f;
}
