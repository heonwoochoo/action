// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/Options/OptionsMenu.h"
#include "Components/Image.h"
#include "HUD/Menu/Options/OptionsWidget.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (OptionClass)
	{
		SelectedOption = Cast<UOptionsWidget>(CreateWidget(this, OptionClass));
		if (SelectedOption)
		{
			SelectedOption->AddToViewport(1);
			SelectedOption->SetOptionsMenu(this);
		}
	}
}

void UOptionsMenu::OnClickedBackButton()
{
	SelectedOption->RemoveFromParent();

	Super::OnClickedBackButton();
}

void UOptionsMenu::SetSelectedOption(UOptionsWidget* Widget)
{
	SelectedOption = Widget;
}

void UOptionsMenu::HideBackgroundImage()
{
	if (BackgroundImage)
	{
		BackgroundImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
