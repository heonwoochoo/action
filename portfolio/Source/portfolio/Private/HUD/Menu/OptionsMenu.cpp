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

	InitBack();

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

void UOptionsMenu::OnHoveredBackButton()
{
	if (ArrowLeft && ActivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(ActivatedArrowLeft);
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredBackButton()
{
	if (ArrowLeft && DeactivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivatedArrowLeft);
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnClickedBackButton()
{
	if (MainMenuClass)
	{
		UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(this, MainMenuClass));
		if (MainMenu)
		{
			MainMenu->AddToViewport();

			SelectedOption->RemoveFromParent();
			RemoveFromParent();
		}
	}
}

void UOptionsMenu::InitBack()
{
	if (BackButton)
	{
		BackButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredBackButton);
		BackButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredBackButton);
		BackButton->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedBackButton);
	}

	if (ArrowLeft && DeactivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivatedArrowLeft);
		ArrowLeft->SetDesiredSizeOverride(FVector2D(48.f));
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::SetSelectedOption(UOptionsWidget* Widget)
{
	SelectedOption = Widget;
}
