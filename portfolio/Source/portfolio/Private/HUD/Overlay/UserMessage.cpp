// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/UserMessage.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/TextBlock.h"

void UUserMessage::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UUserMessage::NotifyMessageToUser(const FText& Message)
{
	SetVisibility(ESlateVisibility::Visible);

	if (NotifyingText)
	{
		NotifyingText->SetText(Message);
	}
	if (ShowHideAnimation)
	{
		PlayAnimationForward(ShowHideAnimation);
	}
}

void UUserMessage::PlayShowHideAnimation()
{
	if (ShowHideAnimation)
	{
		PlayAnimationForward(ShowHideAnimation);
	}
}
