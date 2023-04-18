// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/InGameMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Animation/UMGSequencePlayer.h"
#include "HUD/Menu/InGame/ExitBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"

void UInGameMenu::NativeConstruct()
{
	Super::NativeConstruct();
	InitCharacterButton();
	InitInventoryButton();
	InitQuestButton();
	InitSettingsButton();
	InitSaveButton();
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

void UInGameMenu::OnHoveredSaveButton()
{
	if (SaveButtonImage)
	{
		SaveButtonImage->SetOpacity(1.f);
	}
}

void UInGameMenu::OnUnhoveredSaveButton()
{
	if (SaveButtonImage)
	{
		SaveButtonImage->SetOpacity(0.3f);
	}
}

void UInGameMenu::OnClickedSaveButton()
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
	if (ExitBoxClass)
	{
		ExitBox =  Cast<UExitBox>(CreateWidget(this, ExitBoxClass));
		if (ExitBox)
		{
			ExitBox->AddToViewport();
		}
	}
	
	PlayButtonSound();
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

void UInGameMenu::InitSaveButton()
{
	if (SaveButton)
	{
		SaveButton->OnHovered.AddDynamic(this, &UInGameMenu::OnHoveredSaveButton);
		SaveButton->OnUnhovered.AddDynamic(this, &UInGameMenu::OnUnhoveredSaveButton);
		SaveButton->OnClicked.AddDynamic(this, &UInGameMenu::OnClickedSaveButton);
	}
	if (SaveButtonImage)
	{
		SaveButtonImage->SetOpacity(0.3f);
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

void UInGameMenu::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UInGameMenu::RemoveOpenedWidget()
{
	if (ExitBox)
	{
		ExitBox->RemoveFromParent();
	}
}
