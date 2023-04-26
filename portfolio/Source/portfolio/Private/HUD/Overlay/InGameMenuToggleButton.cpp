// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/InGameMenuToggleButton.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameMode/DefaultGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/HUDBase.h"
#include "Controller/CharacterController.h"

void UInGameMenuToggleButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ShowOverlay)
	{
		PlayAnimationForward(ShowOverlay);
	}
	InitToggleButton();
}

void UInGameMenuToggleButton::OnHoveredToggleButton()
{
	if (ToggleButtonImage && ActivatedRightArrow)
	{
		ToggleButtonImage->SetBrushFromTexture(ActivatedRightArrow);
	}
}

void UInGameMenuToggleButton::OnUnhoveredToggleButton()
{
	if (ToggleButtonImage && DeactivatedRightArrow)
	{
		ToggleButtonImage->SetBrushFromTexture(DeactivatedRightArrow);
	}
}

void UInGameMenuToggleButton::OnClickedToggleButton()
{
	//인게임 메뉴창 오픈
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->OpenInGameMenu();
		}
	}

	// 효과음 재생
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
	DefaultGameMode->PlayCheckButtonClickSound();
	}

	//토글 버튼 제거
	RemoveFromParent();
}

void UInGameMenuToggleButton::InitToggleButton()
{
	if (ToggleButton)
	{
		ToggleButton->OnHovered.AddDynamic(this, &UInGameMenuToggleButton::OnHoveredToggleButton);
		ToggleButton->OnUnhovered.AddDynamic(this, &UInGameMenuToggleButton::OnUnhoveredToggleButton);
		ToggleButton->OnClicked.AddDynamic(this, &UInGameMenuToggleButton::OnClickedToggleButton);
	}
}