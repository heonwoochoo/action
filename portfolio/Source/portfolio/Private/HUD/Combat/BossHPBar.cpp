// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/BossHPBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Animation/WidgetAnimation.h"

void UBossHPBar::NativeConstruct()
{
	if (ShowProgressBar)
	{
		PlayAnimationForward(ShowProgressBar);
	}
}

void UBossHPBar::SetName(const FText& InName)
{
	if (NameText)
	{
		NameText->SetText(InName);
	}
}

void UBossHPBar::OnChangedHP(const float& CurrentHp, const float& MaxHp)
{
	if (!HealthProgressBar) return;
	if (CurrentHp != 0.f)
	{
		HealthProgressBar->SetPercent(CurrentHp / MaxHp);
	}
	else
	{
		HealthProgressBar->SetPercent(0.f);
		RemoveFromParent();
	}
}
