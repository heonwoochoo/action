// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EnemyHPBarWidgetComponent.h"
#include "HUD/EnemyHPBarWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHPBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	HPBarWidget = Cast<UEnemyHPBarWidget>(GetUserWidgetObject());
	HPBarWidget->HPBar->Percent = 0.5f;
}
