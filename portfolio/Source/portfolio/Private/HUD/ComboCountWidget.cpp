// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ComboCountWidget.h"
#include "Components/TextBlock.h"
#include "Animation/UMGSequencePlayer.h"

void UComboCountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndAnimationEvent.BindDynamic(this, &UComboCountWidget::EndHideAnimation);

	if (AnimHideText)
	{
		BindToAnimationFinished(AnimHideText, EndAnimationEvent);
	}
	
	OnVisibilityChanged.AddDynamic(this, &UComboCountWidget::VisibilityChanged);
}

void UComboCountWidget::EndHideAnimation()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UComboCountWidget::VisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Visible)
	{
		if (AnimShowText)
		{
			PlayAnimationForward(AnimShowText);
		}
	}
}

void UComboCountWidget::SetComboCount(int32 Count)
{
	if (ComboCountText)
	{
		ComboCountText->SetText(FText::FromString(FString::FromInt(Count)));
	}
}

void UComboCountWidget::PlayShowAnimation()
{
	if (AnimShowText)
	{
		PlayAnimationForward(AnimShowText);
	}
}

void UComboCountWidget::PlayHideAnimation()
{
	if (AnimHideText)
	{
		PlayAnimationForward(AnimHideText);
	}
}

