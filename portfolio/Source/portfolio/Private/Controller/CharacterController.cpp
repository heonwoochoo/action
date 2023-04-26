// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CharacterController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "HUD/HUDBase.h"

ACharacterController::ACharacterController()
{
	const FVector2D& ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	CharacterInfoInitialLocation = ViewportSize;
	InventoryInitialLocation = ViewportSize;
	QuestInitialLocation = ViewportSize;
}

void ACharacterController::SetInputModeToGame()
{
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();

	// 가이드 메세지 숨김 처리
	AHUDBase* HUDBase = Cast<AHUDBase>(GetHUD());
	if (HUDBase)
	{
		HUDBase->HideGuideMessage();
	}
}

void ACharacterController::SetInputModeToUI()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);

	// 인게임 메뉴 토글버튼 생성
	AHUDBase* HUDBase = Cast<AHUDBase>(GetHUD());
	if (HUDBase)
	{
		HUDBase->CreateInGameMenuToggleButton();
	}
}
