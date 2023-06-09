﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/Start/SubMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "GameInstance/DefaultGameInstance.h"

void USubMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitBack();
}

void USubMenu::OnHoveredBackButton()
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

void USubMenu::OnUnhoveredBackButton()
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

void USubMenu::OnClickedBackButton()
{
	PlayButtonSound();

	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	
	if (DefaultGameInstance)
	{
		if (DefaultGameInstance->IsInGame())
		{
			RemoveFromParent();
			return;
		}
	}
	
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

void USubMenu::InitBack()
{
	if (BackButton)
	{
		BackButton->OnHovered.AddDynamic(this, &USubMenu::OnHoveredBackButton);
		BackButton->OnUnhovered.AddDynamic(this, &USubMenu::OnUnhoveredBackButton);
		BackButton->OnClicked.AddDynamic(this, &USubMenu::OnClickedBackButton);
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

void USubMenu::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}
