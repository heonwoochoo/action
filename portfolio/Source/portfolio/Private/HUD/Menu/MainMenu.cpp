// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/MainMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredStartButton);
	StartButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredStartButton);
	StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedStartButton);
	OptionsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredOptionsButton);
	OptionsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredOptionsButton);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedOptionsButton);
	CreditsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredCreditsButton);
	CreditsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredCreditsButton);
	CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedCreditsButton);
	QuitButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredQuitButton);
	QuitButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredQuitButton);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedQuitButton);
}

void UMainMenu::OnHoveredStartButton()
{
	if (StartButtonImage)
	{
		StartButtonImage->SetOpacity(1.f);
	}
}

void UMainMenu::OnUnhoveredStartButton()
{
	if (StartButtonImage)
	{
		StartButtonImage->SetOpacity(0.f);
	}
}

void UMainMenu::OnClickedStartButton()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DefaultLevel);
	}
}

void UMainMenu::OnHoveredOptionsButton()
{
	if (OptionsButtonImage)
	{
		OptionsButtonImage->SetOpacity(1.f);
	}
}

void UMainMenu::OnUnhoveredOptionsButton()
{
	if (OptionsButtonImage)
	{
		OptionsButtonImage->SetOpacity(0.f);
	}
}

void UMainMenu::OnClickedOptionsButton()
{
	if (OptionsMenuClass)
	{
		UOptionsMenu* OptionMenu = Cast<UOptionsMenu>(CreateWidget(this, OptionsMenuClass));
		if (OptionMenu)
		{
			OptionMenu->AddToViewport();
			RemoveFromParent();
		}
	}
}

void UMainMenu::OnHoveredCreditsButton()
{
	if (CreditsButtonImage)
	{
		CreditsButtonImage->SetOpacity(1.f);
	}
}

void UMainMenu::OnUnhoveredCreditsButton()
{
	if (CreditsButtonImage)
	{
		CreditsButtonImage->SetOpacity(0.f);
	}
}

void UMainMenu::OnClickedCreditsButton()
{
}

void UMainMenu::OnHoveredQuitButton()
{
	if (QuitButtonImage)
	{
		QuitButtonImage->SetOpacity(1.f);
	}
}

void UMainMenu::OnUnhoveredQuitButton()
{
	if (QuitButtonImage)
	{
		QuitButtonImage->SetOpacity(0.f);
	}
}

void UMainMenu::OnClickedQuitButton()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
