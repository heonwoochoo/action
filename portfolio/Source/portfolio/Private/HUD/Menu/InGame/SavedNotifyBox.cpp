﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/SavedNotifyBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "GameMode/DefaultGameMode.h"

void USavedNotifyBox::NativeConstruct()
{
	Super::NativeConstruct();
	InitOKButton();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CharacterController->OnChangedInputMode.AddDynamic(this, &USavedNotifyBox::OnChangedInputMode);
	}
}

void USavedNotifyBox::OnHoveredOKButton()
{
	if (ActivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(ActivatedBox);
	}
}

void USavedNotifyBox::OnUnhoveredOKButton()
{
	if (DeactivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void USavedNotifyBox::OnClickedOKButton()
{
	RemoveFromParent();

	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void USavedNotifyBox::InitOKButton()
{
	if (OKButton)
	{
		OKButton->OnHovered.AddDynamic(this, &USavedNotifyBox::OnHoveredOKButton);
		OKButton->OnUnhovered.AddDynamic(this, &USavedNotifyBox::OnUnhoveredOKButton);
		OKButton->OnClicked.AddDynamic(this, &USavedNotifyBox::OnClickedOKButton);
	}
}

void USavedNotifyBox::OnChangedInputMode(const EInputMode& Mode)
{
	if (Mode == EInputMode::EIM_Game)
	{
		RemoveFromParent();
	}
}
