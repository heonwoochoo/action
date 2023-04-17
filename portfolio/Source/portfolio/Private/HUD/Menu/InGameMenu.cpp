// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGameMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Animation/UMGSequencePlayer.h"

void UInGameMenu::NativeConstruct()
{
	InitCharacterButton();
	InitInventoryButton();
	InitQuestButton();
	InitSettingsButton();
	InitExitButton();

	EndAnimationEvent.BindDynamic(this, &UInGameMenu::OnEndHideAnimation);

	if (AnimHideMenu)
	{
		BindToAnimationFinished(AnimHideMenu, EndAnimationEvent);
	}

	PlayShowAnimation();
}

void UInGameMenu::OnHoveredCharacterButton()
{
	if (CharacterButtonImage)
	{
		CharacterButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredCharacterButton()
{
	if (CharacterButtonImage)
	{
		CharacterButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedCharacterButton()
{
}

void UInGameMenu::OnHoveredInventoryButton()
{
	if (InventoryButtonImage)
	{
		InventoryButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredInventoryButton()
{
	if (InventoryButtonImage)
	{
		InventoryButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedInventoryButton()
{
}

void UInGameMenu::OnHoveredQuestButton()
{
	if (QuestButtonImage)
	{
		QuestButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredQuestButton()
{
	if (QuestButtonImage)
	{
		QuestButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedQuestButton()
{
}

void UInGameMenu::OnHoveredSettingsButton()
{
	if (SettingsButtonImage)
	{
		SettingsButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredSettingsButton()
{
	if (SettingsButtonImage)
	{
		SettingsButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedSettingsButton()
{
}

void UInGameMenu::OnHoveredExitButton()
{
	if (ExitButtonImage)
	{
		ExitButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredExitButton()
{
	if (ExitButtonImage)
	{
		ExitButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedExitButton()
{
}

void UInGameMenu::InitCharacterButton()
{
	if (CharacterButton)
	{
		CharacterButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredCharacterButton);
		CharacterButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredCharacterButton);
		CharacterButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedCharacterButton);
	}
	if (CharacterButtonImage)
	{
		CharacterButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::InitInventoryButton()
{
	if (InventoryButton)
	{
		InventoryButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredInventoryButton);
		InventoryButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredInventoryButton);
		InventoryButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedInventoryButton);
	}
	if (InventoryButtonImage)
	{
		InventoryButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::InitQuestButton()
{
	if (QuestButton)
	{
		QuestButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredQuestButton);
		QuestButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredQuestButton);
		QuestButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedQuestButton);
	}
	if (QuestButtonImage)
	{
		QuestButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::InitSettingsButton()
{
	if (SettingsButton)
	{
		SettingsButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredSettingsButton);
		SettingsButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredSettingsButton);
		SettingsButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedSettingsButton);
	}
	if (SettingsButtonImage)
	{
		SettingsButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::InitExitButton()
{
	if (ExitButton)
	{
		ExitButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredExitButton);
		ExitButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredExitButton);
		ExitButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedExitButton);
	}
	if (ExitButtonImage)
	{
		ExitButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::PlayShowAnimation()
{
	if (AnimShowMenu)
	{
		PlayAnimationForward(AnimShowMenu);
	}
}

void UInGameMenu::PlayHideAnimation()
{
	if (AnimHideMenu)
	{
		PlayAnimationForward(AnimHideMenu);
	}
}

void UInGameMenu::OnEndHideAnimation()
{
	RemoveFromParent();
}
