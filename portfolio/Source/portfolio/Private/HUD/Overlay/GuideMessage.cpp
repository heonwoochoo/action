// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/GuideMessage.h"
#include "Components/TextBlock.h"

void UGuideMessage::NativeConstruct()
{
	Super::NativeConstruct();

	HideGuideMessage();
}

void UGuideMessage::ShowGuideMessage(const FText& Message)
{
	if (GuideText)
	{
		GuideText->SetText(Message);
		GuideText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGuideMessage::HideGuideMessage()
{
	if (GuideText)
	{
		GuideText->SetVisibility(ESlateVisibility::Hidden);
	}
}