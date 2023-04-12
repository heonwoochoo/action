// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/MainMunu.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UMainMunu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnHovered.AddDynamic(this, &UMainMunu::OnHoveredStartButton);
	StartButton->OnUnhovered.AddDynamic(this, &UMainMunu::OnUnhoveredStartButton);
	OptionsButton->OnHovered.AddDynamic(this, &UMainMunu::OnHoveredOptionsButton);
	OptionsButton->OnUnhovered.AddDynamic(this, &UMainMunu::OnUnhoveredOptionsButton);
	CreditsButton->OnHovered.AddDynamic(this, &UMainMunu::OnHoveredCreditsButton);
	CreditsButton->OnUnhovered.AddDynamic(this, &UMainMunu::OnUnhoveredCreditsButton);
	QuitButton->OnHovered.AddDynamic(this, &UMainMunu::OnHoveredQuitButton);
	QuitButton->OnUnhovered.AddDynamic(this, &UMainMunu::OnUnhoveredQuitButton);
}

void UMainMunu::OnHoveredStartButton()
{
	if (StartButtonImage)
	{
		StartButtonImage->SetOpacity(1.f);
	}
}

void UMainMunu::OnUnhoveredStartButton()
{
	if (StartButtonImage)
	{
		StartButtonImage->SetOpacity(0.f);
	}
}

void UMainMunu::OnHoveredOptionsButton()
{
	if (OptionsButtonImage)
	{
		OptionsButtonImage->SetOpacity(1.f);
	}
}

void UMainMunu::OnUnhoveredOptionsButton()
{
	if (OptionsButtonImage)
	{
		OptionsButtonImage->SetOpacity(0.f);
	}
}

void UMainMunu::OnHoveredCreditsButton()
{
	if (CreditsButtonImage)
	{
		CreditsButtonImage->SetOpacity(1.f);
	}
}

void UMainMunu::OnUnhoveredCreditsButton()
{
	if (CreditsButtonImage)
	{
		CreditsButtonImage->SetOpacity(0.f);
	}
}

void UMainMunu::OnHoveredQuitButton()
{
	if (QuitButtonImage)
	{
		QuitButtonImage->SetOpacity(1.f);
	}
}

void UMainMunu::OnUnhoveredQuitButton()
{
	if (QuitButtonImage)
	{
		QuitButtonImage->SetOpacity(0.f);
	}
}
