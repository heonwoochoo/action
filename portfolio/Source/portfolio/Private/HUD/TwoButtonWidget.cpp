// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TwoButtonWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"

void UTwoButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitOKButton();
	InitCancelButton();
}

void UTwoButtonWidget::OnHoveredOKButton()
{
	if (ActivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UTwoButtonWidget::OnUnhoveredOKButton()
{
	if (DeactivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UTwoButtonWidget::OnClickedOKButton()
{
	PlayButtonSound();
}

void UTwoButtonWidget::OnHoveredCancelButton()
{
	if (ActivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UTwoButtonWidget::OnUnhoveredCancelButton()
{
	if (DeactivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UTwoButtonWidget::OnClickedCancelButton()
{
	RemoveFromParent();

	PlayButtonSound();
}

void UTwoButtonWidget::InitOKButton()
{
	if (OKButton)
	{
		OKButton->OnHovered.AddDynamic(this, &UTwoButtonWidget::OnHoveredOKButton);
		OKButton->OnUnhovered.AddDynamic(this, &UTwoButtonWidget::OnUnhoveredOKButton);
		OKButton->OnClicked.AddDynamic(this, &UTwoButtonWidget::OnClickedOKButton);
	}
}

void UTwoButtonWidget::InitCancelButton()
{
	if (CancelButton)
	{
		CancelButton->OnHovered.AddDynamic(this, &UTwoButtonWidget::OnHoveredCancelButton);
		CancelButton->OnUnhovered.AddDynamic(this, &UTwoButtonWidget::OnUnhoveredCancelButton);
		CancelButton->OnClicked.AddDynamic(this, &UTwoButtonWidget::OnClickedCancelButton);
	}
}

void UTwoButtonWidget::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}