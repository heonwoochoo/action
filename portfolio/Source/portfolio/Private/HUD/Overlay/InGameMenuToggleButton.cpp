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

	InitToggleButton();
}

void UInGameMenuToggleButton::OnHoveredToggleButton()
{
	if (ToggleButtonImage && ActivatedRightArrow)
	{
		ToggleButtonImage->SetBrushFromTexture(ActivatedRightArrow);
	}

	// 가이드 메세지 나타남
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			const FText& Message = FText::FromString(TEXT("클릭 시 메뉴가 나타납니다."));
			HUDBase->ShowGuideMessage(Message);
		}
	}
}

void UInGameMenuToggleButton::OnUnhoveredToggleButton()
{
	if (ToggleButtonImage && DeactivatedRightArrow)
	{
		ToggleButtonImage->SetBrushFromTexture(DeactivatedRightArrow);
	}

	// 가이드 메세지 숨김
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

void UInGameMenuToggleButton::OnClickedToggleButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Toggle clicked!"));
	//인게임 메뉴창 오픈
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->ShowInGameMenu();
		}
	}

	// 효과음 재생
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
	DefaultGameMode->PlayCheckButtonClickSound();
	}

	//토글 버튼 숨김
	SetVisibility(ESlateVisibility::Hidden);
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

void UInGameMenuToggleButton::PlayShowAnimation()
{
	if (ShowOverlay)
	{
		PlayAnimationForward(ShowOverlay);
	}
}