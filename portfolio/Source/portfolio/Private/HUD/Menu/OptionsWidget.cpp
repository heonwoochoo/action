// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "HUD/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultGameMode.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitReset();
	InitConfirm();
	InitOptionChangeButton();
}

void UOptionsWidget::OnHoveredReset()
{
	if (ResetImage && ActivatedBox)
	{
		ResetImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UOptionsWidget::OnUnhoveredReset()
{
	if (ResetImage && DeactivatedBox)
	{
		ResetImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UOptionsWidget::OnClickedReset()
{
	PlayBoxButtonSound();
}

void UOptionsWidget::OnHoveredConfirm()
{
	if (ConfirmImage && ActivatedBox)
	{
		ConfirmImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UOptionsWidget::OnUnhoveredConfirm()
{
	if (ConfirmImage && DeactivatedBox)
	{
		ConfirmImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UOptionsWidget::OnClickedConfirm()
{
	PlayBoxButtonSound();
}

void UOptionsWidget::OnHoveredOptionLeftButton()
{
	if (ActivatedLargeArrowLeft && OptionLeftImage)
	{
		OptionLeftImage->SetBrushFromTexture(ActivatedLargeArrowLeft);
	}
}

void UOptionsWidget::OnUnhoveredOptionLeftButton()
{
	if (DeactivatedLargeArrowLeft && OptionLeftImage)
	{
		OptionLeftImage->SetBrushFromTexture(DeactivatedLargeArrowLeft);
	}
}

void UOptionsWidget::OnHoveredOptionRightButton()
{
	if (ActivatedLargeArrowRight && OptionRightImage)
	{
		OptionRightImage->SetBrushFromTexture(ActivatedLargeArrowRight);
	}
}

void UOptionsWidget::OnUnhoveredOptionRightButton()
{
	if (DeactivatedLargeArrowRight && OptionRightImage)
	{
		OptionRightImage->SetBrushFromTexture(DeactivatedLargeArrowRight);
	}
}

void UOptionsWidget::OnClickedOptionChangeButton()
{
	if (OptionsWidgetClass)
	{
		UOptionsWidget* OptionsWidget = Cast<UOptionsWidget>(CreateWidget(this, OptionsWidgetClass));
		if (OptionsWidget)
		{
			OptionsWidget->SetOptionsMenu(OptionsMenu);
			OptionsWidget->AddToViewport(1);
			OptionsMenu->SetSelectedOption(OptionsWidget);
			RemoveFromParent();
		}
	}

	PlayChangeButtonSound();
}

void UOptionsWidget::InitReset()
{
	if (ResetButton)
	{
		ResetButton->OnHovered.AddDynamic(this, &UOptionsWidget::OnHoveredReset);
		ResetButton->OnUnhovered.AddDynamic(this, &UOptionsWidget::OnUnhoveredReset);
		ResetButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnClickedReset);
	}
}

void UOptionsWidget::InitConfirm()
{
	if (ConfirmButton)
	{
		ConfirmButton->OnHovered.AddDynamic(this, &UOptionsWidget::OnHoveredConfirm);
		ConfirmButton->OnUnhovered.AddDynamic(this, &UOptionsWidget::OnUnhoveredConfirm);
		ConfirmButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnClickedConfirm);
	}
}

void UOptionsWidget::InitOptionChangeButton()
{
	if (OptionLeftButton)
	{
		OptionLeftButton->OnHovered.AddDynamic(this, &UOptionsWidget::OnHoveredOptionLeftButton);
		OptionLeftButton->OnUnhovered.AddDynamic(this, &UOptionsWidget::OnUnhoveredOptionLeftButton);
		OptionLeftButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnClickedOptionChangeButton);
	}
	if (OptionRightButton)
	{
		OptionRightButton->OnHovered.AddDynamic(this, &UOptionsWidget::OnHoveredOptionRightButton);
		OptionRightButton->OnUnhovered.AddDynamic(this, &UOptionsWidget::OnUnhoveredOptionRightButton);
		OptionRightButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnClickedOptionChangeButton);
	}
}

void UOptionsWidget::PlayChangeButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UOptionsWidget::PlayBoxButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UOptionsWidget::SetOptionsMenu(UOptionsMenu* Widget)
{
	OptionsMenu = Widget;
}
