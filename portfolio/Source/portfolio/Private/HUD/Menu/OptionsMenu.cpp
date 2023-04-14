// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/MainMenu.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Components/ProgressBar.h"
#include "HUD/Menu/OptionsWidget.h"

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