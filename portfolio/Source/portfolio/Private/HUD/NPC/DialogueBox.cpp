// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NPC/DialogueBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"

void UDialogueBox::NativeConstruct()
{
	InitCloseButton();
	InitPrevButton();
	InitNextButton();
}

void UDialogueBox::OnHoveredCloseButton()
{
	if (CloseButtonImage && ActivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredCloseButton()
{
	if (CloseButtonImage && DeactivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedCloseButton()
{

	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UDialogueBox::OnHoveredPrevButton()
{
	if (PrevButtonImage && ActivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredPrevButton()
{
	if (PrevButtonImage && DeactivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedPrevButton()
{
	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UDialogueBox::OnHoveredNextButton()
{
	if (NextButtonImage && ActivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredNextButton()
{
	if (NextButtonImage && DeactivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedNextButton()
{
	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UDialogueBox::InitCloseButton()
{
	if (CloseButton)
	{
		CloseButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredCloseButton);
		CloseButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredCloseButton);
		CloseButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedCloseButton);
	}
	if (CloseButtonImage && DeactivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::InitPrevButton()
{
	if (PrevButton)
	{
		PrevButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredPrevButton);
		PrevButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredPrevButton);
		PrevButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedPrevButton);
	}
	if (PrevButtonImage && DeactivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::InitNextButton()
{
	if (NextButton)
	{
		NextButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredNextButton);
		NextButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredNextButton);
		NextButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedNextButton);
	}
	if (NextButtonImage && DeactivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}