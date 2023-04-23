// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/MovableWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"
#include "HUD/HUDBase.h"
#include "Components/Overlay.h"

void UMovableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	InitTitleDragButton();
	InitExitButton();

	InitCanvasLocation();
}

void UMovableWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCanMovable && InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
			const float NewX = MouseLocation.X - OffsetX;
			const float NewY = MouseLocation.Y - OffsetY;
			CanvasPanelSlot->SetPosition(FVector2D(NewX, NewY));
		}
	}
}

void UMovableWidget::NativeDestruct()
{
	Super::NativeDestruct();


	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		// 인풋모드 변경
		CharacterController->SetInputModeToGame();

		// 툴팁 열려있으면 닫기
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->HideItemTooltip();
		}
	}

	// 오픈 상태 변수 변경
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		DefaultCharacter->SetIsOpenInGameMenu(false);
	}
}

void UMovableWidget::OnHoveredTitleDragButton()
{
	if (ActivatedTitleBox && TitleTextImage)
	{
		TitleTextImage->SetBrushFromTexture(ActivatedTitleBox);
	}
}

void UMovableWidget::OnUnhoveredTitleDragButton()
{
	if (DeactivatedTitleBox && TitleTextImage)
	{
		TitleTextImage->SetBrushFromTexture(DeactivatedTitleBox);
	}
}

void UMovableWidget::OnPressedTitleDragButton()
{
	if (TitleDragOverlay)
	{
		TitleDragOverlay->SetRenderOpacity(0.5f);
	}

	bCanMovable = true;

	// 마우스와 캔버스의 간격 저장
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
	if (CanvasPanelSlot)
	{
		const FVector2D& CanvasLocation = CanvasPanelSlot->GetPosition();
		const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		OffsetX = MouseLocation.X - CanvasLocation.X;
		OffsetY = MouseLocation.Y - CanvasLocation.Y;
	}
}

void UMovableWidget::OnReleasedTitleDragButton()
{
	if (TitleDragOverlay)
	{
		TitleDragOverlay->SetRenderOpacity(1.f);
	}
	bCanMovable = false;
}

void UMovableWidget::OnHoveredExitButton()
{
	if (ActivatedExitButton && ExitButtonImage)
	{
		ExitButtonImage->SetBrushFromTexture(ActivatedExitButton);
	}
}

void UMovableWidget::OnUnhoveredExitButton()
{
	if (DeactivatedExitButton && ExitButtonImage)
	{
		ExitButtonImage->SetBrushFromTexture(DeactivatedExitButton);
	}
}

void UMovableWidget::OnClickedExitButton()
{
	PlayButtonSound();

	RemoveFromParent();
}

void UMovableWidget::InitTitleDragButton()
{
	if (TitleDragButton)
	{
		TitleDragButton->OnHovered.AddDynamic(this, &UMovableWidget::OnHoveredTitleDragButton);
		TitleDragButton->OnUnhovered.AddDynamic(this, &UMovableWidget::OnUnhoveredTitleDragButton);
		TitleDragButton->OnPressed.AddDynamic(this, &UMovableWidget::OnPressedTitleDragButton);
		TitleDragButton->OnReleased.AddDynamic(this, &UMovableWidget::OnReleasedTitleDragButton);
	}
}

void UMovableWidget::InitExitButton()
{
	if (ExitButton)
	{
		ExitButton->OnHovered.AddDynamic(this, &UMovableWidget::OnHoveredExitButton);
		ExitButton->OnUnhovered.AddDynamic(this, &UMovableWidget::OnUnhoveredExitButton);
		ExitButton->OnClicked.AddDynamic(this, &UMovableWidget::OnClickedExitButton);
	}
}

void UMovableWidget::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UMovableWidget::InitCanvasLocation()
{
}
