// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/Options/OptionsMenu.h"
#include "Components/Image.h"
#include "HUD/Menu/Options/OptionsWidget.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/DefaultGameInstance.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (OptionClass)
	{
		SelectedOption = Cast<UOptionsWidget>(CreateWidget(this, OptionClass));
		if (SelectedOption)
		{
			SelectedOption->AddToViewport(1);
			SelectedOption->SetOptionsMenu(this);
		}
	}
}

void UOptionsMenu::NativeDestruct()
{
	Super::NativeDestruct();

	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (DefaultGameInstance && DefaultGameInstance->IsInGame())
	{
		// 인풋 모드 변경
		ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
		if (CharacterController)
		{
			CharacterController->SetInputModeToGame();
		}
		// 오픈 상태 변수 변경
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (DefaultCharacter)
		{
			DefaultCharacter->SetIsOpenInGameMenu(false);
		}
	}

	// 열려있는 자식 위젯 닫기
	if (SelectedOption)
	{
		SelectedOption->RemoveFromParent();
	}
}

void UOptionsMenu::OnClickedBackButton()
{
	Super::OnClickedBackButton();
}

void UOptionsMenu::SetSelectedOption(UOptionsWidget* Widget)
{
	SelectedOption = Widget;
}

void UOptionsMenu::HideBackgroundImage()
{
	if (BackgroundImage)
	{
		BackgroundImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
