// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/StartMenu.h"
#include "Components/StackBox.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitNewButton();
	InitLoadButton();
	InitDeleteButton();
}

void UStartMenu::OnHoveredNewButton()
{
	if (NewImage && ActivatedBox)
	{
		NewImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredNewButton()
{
	if (NewImage && DeactivatedBox)
	{
		NewImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedNewButton()
{
	PlayButtonSound();
}

void UStartMenu::OnHoveredLoadButton()
{
	if (LoadImage && ActivatedBox)
	{
		LoadImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredLoadButton()
{
	if (LoadImage && DeactivatedBox)
	{
		LoadImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedLoadButton()
{
	PlayButtonSound();
}

void UStartMenu::OnHoveredDeleteButton()
{
	if (DeleteImage && ActivatedBox)
	{
		DeleteImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredDeleteButton()
{
	if (DeleteImage && DeactivatedBox)
	{
		DeleteImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedDeleteButton()
{
	PlayButtonSound();
}

void UStartMenu::InitNewButton()
{
	if (NewButton)
	{
		NewButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredNewButton);
		NewButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredNewButton);
		NewButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedNewButton);
	}
}

void UStartMenu::InitLoadButton()
{
	if (LoadButton)
	{
		LoadButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredLoadButton);
		LoadButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredLoadButton);
		LoadButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedLoadButton);
	}
}

void UStartMenu::InitDeleteButton()
{
	if (DeleteButton)
	{
		DeleteButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredDeleteButton);
		DeleteButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredDeleteButton);
		DeleteButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedDeleteButton);
	}
}
