// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/InGameMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Animation/UMGSequencePlayer.h"
#include "HUD/Menu/InGame/ExitBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "GameInstance/DefaultGameInstance.h"
#include "HUD/Menu/InGame/SavedNotifyBox.h"
#include "HUD/Menu/InGame/Inventory.h"
#include "HUD/Menu/Options/OptionsMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "HUD/Menu/InGame/CharacterInfo.h"
#include "HUD/HUDBase.h"
#include "Controller/CharacterController.h"

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

	if (HideMenu)
	{
		BindToAnimationFinished(HideMenu, EndAnimationEvent);
	}

	AllChildWidgetClasses = { ExitBoxClass, SavedNotifyBoxClass, InventoryClass, OptionsMenuClass, CharacterInfoClass };
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->SetInGameMenuChildWidgetClasses(AllChildWidgetClasses);
		}
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
	PlayButtonSound();
	if (InventoryClass)
	{
		UCharacterInfo* CharacterInfo = Cast<UCharacterInfo>(CreateWidget(this, CharacterInfoClass));
		if (CharacterInfo)
		{
			CharacterInfo->AddToViewport();

			//인게임 메뉴 닫기
			PlayHideAnimation();
		}
	}
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
	PlayButtonSound();
	if (InventoryClass)
	{
		UInventory* Inventory = Cast<UInventory>(CreateWidget(this, InventoryClass));
		if (Inventory)
		{
			Inventory->AddToViewport();
			
			//인게임 메뉴 닫기
			PlayHideAnimation();
		}
	}
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
	PlayButtonSound();

	if (OptionsMenuClass)
	{
		UOptionsMenu* OptionsMenu = Cast<UOptionsMenu>(CreateWidget(this, OptionsMenuClass));
		if (OptionsMenu)
		{
			OptionsMenu->AddToViewport();
			OptionsMenu->HideBackgroundImage();

			//인게임 메뉴 닫기
			PlayHideAnimation();
		}
	}
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
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance && SavedNotifyBoxClass)
	{
		// 데이터 업데이트
		DefaultGameInstance->UpdateSaveGame();

		// 저장
		bool IsSuccess = DefaultGameInstance->SaveGame();
		if (IsSuccess)
		{
			// 성공 알림 박스
			SavedNotifyBox = Cast<USavedNotifyBox>(CreateWidget(this, SavedNotifyBoxClass));
			if (SavedNotifyBox)
			{
				SavedNotifyBox->AddToViewport();
			}
		}
	}
	PlayButtonSound();
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
	RemoveFromParent();
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
	if (ShowMenu)
	{
		PlayAnimationForward(ShowMenu);
	}
}

void UInGameMenu::PlayHideAnimation()
{
	if (HideMenu)
	{
		PlayAnimationForward(HideMenu);
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
	for (const auto& WidgetClass : AllChildWidgetClasses)
	{
		TArray<UUserWidget*> FoundWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidget, WidgetClass);
		if (FoundWidget.Num() >= 1)
		{
			for (auto Widget : FoundWidget)
			{
				Widget->RemoveFromParent();
			}
		}
	}
}