// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/UserCreateBox.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultGameMode.h"

void UUserCreateBox::NativeConstruct()
{
	Super::NativeConstruct();

	InitOKButton();
	InitCancelButton();
}

void UUserCreateBox::OnHoveredOKButton()
{
	if (ActivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UUserCreateBox::OnUnhoveredOKButton()
{
	if (DeactivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UUserCreateBox::OnClickedOKButton()
{
	PlayButtonSound();
}

void UUserCreateBox::OnHoveredCancelButton()
{
	if (ActivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UUserCreateBox::OnUnhoveredCancelButton()
{
	if (DeactivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UUserCreateBox::OnClickedCancelButton()
{
	RemoveFromParent();

	PlayButtonSound();
}

void UUserCreateBox::InitOKButton()
{
	if (OKButton)
	{
		OKButton->OnHovered.AddDynamic(this, &UUserCreateBox::OnHoveredOKButton);
		OKButton->OnUnhovered.AddDynamic(this, &UUserCreateBox::OnUnhoveredOKButton);
		OKButton->OnClicked.AddDynamic(this, &UUserCreateBox::OnClickedOKButton);
	}
}

void UUserCreateBox::InitCancelButton()
{
	if (CancelButton)
	{
		CancelButton->OnHovered.AddDynamic(this, &UUserCreateBox::OnHoveredCancelButton);
		CancelButton->OnUnhovered.AddDynamic(this, &UUserCreateBox::OnUnhoveredCancelButton);
		CancelButton->OnClicked.AddDynamic(this, &UUserCreateBox::OnClickedCancelButton);
	}
}

void UUserCreateBox::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}