// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/EnemyHPBarWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HPBar)
	{
		HPBar->SetPercent(1.0f);
	}
}
