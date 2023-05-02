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

void UEnemyHPBarWidget::OnChangedEnemyHP(const float& CurrentHp, const float& MaxHp)
{
	if (!HPBar) return;
	if (CurrentHp != 0.f)
	{
		HPBar->SetPercent(CurrentHp / MaxHp);
	}
	else
	{
		HPBar->SetPercent(0.f);
	}
}
