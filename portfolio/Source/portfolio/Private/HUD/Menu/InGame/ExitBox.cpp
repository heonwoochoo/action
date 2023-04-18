// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ExitBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"

void UExitBox::NativeConstruct()
{
	InitReturnSMenuButton();
	InitExitGameButton();
	InitCancelButton();
}

void UExitBox::OnHoveredReturnSMenuButton()
{
	if (ActivatedBox && ReturnSMenuImage)
	{
		ReturnSMenuImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredReturnSMenuButton()
{
	if (DeactivatedBox && ReturnSMenuImage)
	{
		ReturnSMenuImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedReturnSMenuButton()
{
	PlayButtonSound();
}

void UExitBox::OnHoveredExitGameButton()
{
	if (ActivatedBox && ExitGamelImage)
	{
		ExitGamelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredExitGameButton()
{
	if (DeactivatedBox && ExitGamelImage)
	{
		ExitGamelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedExitGameButton()
{
	
	PlayButtonSound();
}

void UExitBox::OnHoveredCancelButton()
{
	if (ActivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredCancelButton()
{
	if (DeactivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedCancelButton()
{
	RemoveFromParent();
	PlayButtonSound();
}

void UExitBox::InitReturnSMenuButton()
{
	if (ReturnSMenuButton)
	{
		ReturnSMenuButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredReturnSMenuButton);
		ReturnSMenuButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredReturnSMenuButton);
		ReturnSMenuButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedReturnSMenuButton);
	}
}

void UExitBox::InitExitGameButton()
{
	if (ExitGameButton)
	{
		ExitGameButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredExitGameButton);
		ExitGameButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredExitGameButton);
		ExitGameButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedExitGameButton);
	}
}

void UExitBox::InitCancelButton()
{
	if (CancelButton)
	{
		CancelButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredCancelButton);
		CancelButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredCancelButton);
		CancelButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedCancelButton);
	}
}

void UExitBox::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}
