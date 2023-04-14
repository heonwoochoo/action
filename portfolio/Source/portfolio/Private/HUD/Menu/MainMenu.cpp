// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/MainMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DefaultGameMode.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitStartButton();
	InitOptionsButton();
	InitCreditsButton();
	InitQuitButton();
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
	// 오픈월드 열기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DefaultLevel);
	}

	PlayButtonClickSound();
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
	// 옵션 메뉴 열기
	if (OptionsMenuClass)
	{
		UOptionsMenu* OptionMenu = Cast<UOptionsMenu>(CreateWidget(this, OptionsMenuClass));
		if (OptionMenu)
		{
			OptionMenu->AddToViewport();
			RemoveFromParent();
		}
	}

	PlayButtonClickSound();
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
	PlayButtonClickSound();
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
	// 게임종료
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
	PlayButtonClickSound();
}

void UMainMenu::InitStartButton()
{
	if (StartButton)
	{
		StartButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredStartButton);
		StartButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredStartButton);
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedStartButton);
	}
}

void UMainMenu::InitOptionsButton()
{
	if (OptionsButton)
	{
		OptionsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredOptionsButton);
		OptionsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredOptionsButton);
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedOptionsButton);
	}
}

void UMainMenu::InitCreditsButton()
{
	if (CreditsButton)
	{
		CreditsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredCreditsButton);
		CreditsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredCreditsButton);
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedCreditsButton);
	}
}

void UMainMenu::InitQuitButton()
{
	if (QuitButton)
	{
		QuitButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredQuitButton);
		QuitButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnhoveredQuitButton);
		QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnClickedQuitButton);
	}
}

void UMainMenu::PlayButtonClickSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}
