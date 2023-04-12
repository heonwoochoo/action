// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredBackButton);
		BackButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredBackButton);
	}

	if (ArrowLeft && DeactivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivedArrowLeft);
		ArrowLeft->SetBrushSize(FVector2D(48.f));
	}
}

void UOptionsMenu::OnHoveredBackButton()
{
	if (ArrowLeft && ActivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(ActivedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredBackButton()
{
	if (ArrowLeft && DeactivedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivedArrowLeft);
	}
}
