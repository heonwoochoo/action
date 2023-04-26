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

void UInGameMenu::NativeDestruct()
{
	Super::NativeDestruct();

	HideGuideMessage();
}



void UInGameMenu::OnHoveredCharacterButton()
{
	if (CharacterButtonImage)
	{
		CharacterButtonImage->SetOpacity(1.f);
	}

	const FText Message = FText::FromString(TEXT("캐릭터의 스탯과 착용한 장비를 확인합니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredCharacterButton()
{
	if (CharacterButtonImage)
	{
		CharacterButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
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

			HideGuideMessage();

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
	const FText Message = FText::FromString(TEXT("인벤토리를 열어 현재 가지고 있는 아이템을 확인합니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredInventoryButton()
{
	if (InventoryButtonImage)
	{
		InventoryButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
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
			
			HideGuideMessage();

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
	const FText Message = FText::FromString(TEXT("퀘스트 목록을 확인합니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredQuestButton()
{
	if (QuestButtonImage)
	{
		QuestButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
}

void UInGameMenu::OnClickedQuestButton()
{
	HideGuideMessage();
}

void UInGameMenu::OnHoveredSettingsButton()
{
	if (SettingsButtonImage)
	{
		SettingsButtonImage->SetOpacity(1.f);
	}
	const FText Message = FText::FromString(TEXT("그래픽 성능과 음향을 조절할 수 있습니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredSettingsButton()
{
	if (SettingsButtonImage)
	{
		SettingsButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
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

			HideGuideMessage();

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
	const FText Message = FText::FromString(TEXT("현재까지의 게임 상태를 저장할 수 있습니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredSaveButton()
{
	if (SaveButtonImage)
	{
		SaveButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
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
	HideGuideMessage();
	PlayButtonSound();
}

void UInGameMenu::OnHoveredExitButton()
{
	if (ExitButtonImage)
	{
		ExitButtonImage->SetOpacity(1.f);
	}
	const FText Message = FText::FromString(TEXT("게임을 종료하거나 시작 메뉴로 돌아갑니다."));
	ShowGuideMessage(Message);
}

void UInGameMenu::OnUnhoveredExitButton()
{
	if (ExitButtonImage)
	{
		ExitButtonImage->SetOpacity(0.3f);
	}
	HideGuideMessage();
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

void UInGameMenu::ShowGuideMessage(const FText& Message)
{
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->ShowGuideMessage(Message);
		}
	}
}

void UInGameMenu::HideGuideMessage()
{
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->HideGuideMessage();
		}
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