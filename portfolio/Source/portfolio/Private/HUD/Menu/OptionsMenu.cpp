// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/MainMenu.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredBackButton);
		BackButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredBackButton);
		BackButton->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedBackButton);
	}

	if (ArrowLeft && DeactivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivedArrowLeft);
		ArrowLeft->SetDesiredSizeOverride(FVector2D(48.f));
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredBackButton()
{
	if (ArrowLeft && ActivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(ActivedArrowLeft);
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredBackButton()
{
	if (ArrowLeft && DeactivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivedArrowLeft);
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
			RemoveFromParent();
		}
	}
}

void UOptionsMenu::OnHoveredWindowMode()
{
}

void UOptionsMenu::OnUnhoveredWindowMode()
{
}

void UOptionsMenu::OnHoveredWindowModeArrowLeft()
{
}

void UOptionsMenu::OnUnhoveredWindowModeArrowLeft()
{
}

void UOptionsMenu::OnHoveredWindowModeArrowRight()
{
}

void UOptionsMenu::OnUnhoveredWindowModeArrowRight()
{
}
