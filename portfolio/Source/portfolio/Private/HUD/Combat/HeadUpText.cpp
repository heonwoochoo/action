// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/HeadUpText.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UHeadUpText::NativeConstruct()
{
	Super::NativeConstruct();

	if (FloatUp)
	{
		PlayAnimationForward(FloatUp);
	}
}

void UHeadUpText::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (Animation == FloatUp)
	{
		RemoveFromParent();
	}
}

void UHeadUpText::SetShowingText(const FText& InText, const FColor& Color)
{
	if (ShowingText)
	{
		ShowingText->SetText(InText);
		ShowingText->SetColorAndOpacity(Color);
	}
}
