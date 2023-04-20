// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/Inventory.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	InitInventoryDragButton();
	InitEquipmentTabButton();
	InitConsumableTabButton();
	InitExitButton();

	InitCanvasLocation();
}

void UInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCanMovable && InventoryCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
			const float NewX = MouseLocation.X - OffsetX;
			const float NewY = MouseLocation.Y - OffsetY;
			CanvasPanelSlot->SetPosition(FVector2D(NewX, NewY));
		}
	}
}

void UInventory::NativeDestruct()
{
	Super::NativeDestruct();

	// 인풋모드 변경
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

void UInventory::OnHoveredInventoryDragButton()
{
	if (ActivatedBox && InventoryTextImage)
	{
		InventoryTextImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UInventory::OnUnhoveredInventoryDragButton()
{
	if (DeactivatedExitButton && InventoryTextImage)
	{
		InventoryTextImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UInventory::OnPressedInventoryDragButton()
{
	if (InventoryDragOverlay)
	{
		InventoryDragOverlay->SetRenderOpacity(0.5f);
	}

	bCanMovable = true;

	// 마우스와 캔버스의 간격 저장
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryCanvas);
	if (CanvasPanelSlot)
	{
		const FVector2D& CanvasLocation = CanvasPanelSlot->GetPosition();
		const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		OffsetX = MouseLocation.X - CanvasLocation.X;
		OffsetY = MouseLocation.Y - CanvasLocation.Y;
	}
}

void UInventory::OnReleasedInventoryDragButton()
{
	if (InventoryDragOverlay)
	{
		InventoryDragOverlay->SetRenderOpacity(1.f);
	}

	// 위치저장
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{	
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& CurrentLocation = CanvasPanelSlot->GetPosition();
			CharacterController->SetInventoryInitialLocation(CurrentLocation);
		}
	}

	bCanMovable = false;
}

void UInventory::OnHoveredEquipmentTabButton()
{
}

void UInventory::OnUnhoveredEquipmentTabButton()
{
}

void UInventory::OnClickedEquipmentTabButton()
{
	
}

void UInventory::OnHoveredConsumableTabButton()
{
}

void UInventory::OnUnhoveredConsumableTabButton()
{
}

void UInventory::OnClickedConsumableTabButton()
{
}

void UInventory::OnHoveredExitButton()
{
	if (ActivatedExitButton && ExitButtonImage)
	{
		ExitButtonImage->SetBrushFromTexture(ActivatedExitButton);
	}
}

void UInventory::OnUnhoveredExitButton()
{
	if (DeactivatedExitButton && ExitButtonImage)
	{
		ExitButtonImage->SetBrushFromTexture(DeactivatedExitButton);
	}
}

void UInventory::OnClickedExitButton()
{
	PlayButtonSound();



	RemoveFromParent();
}

void UInventory::InitInventoryDragButton()
{
	if (InventoryDragButton)
	{
		InventoryDragButton->OnHovered.AddDynamic(this, &UInventory::OnHoveredInventoryDragButton);
		InventoryDragButton->OnUnhovered.AddDynamic(this, &UInventory::OnUnhoveredInventoryDragButton);
		InventoryDragButton->OnPressed.AddDynamic(this, &UInventory::OnPressedInventoryDragButton);
		InventoryDragButton->OnReleased.AddDynamic(this, &UInventory::OnReleasedInventoryDragButton);
	}
}

void UInventory::InitEquipmentTabButton()
{
	if (EquipmentTabButton)
	{
		EquipmentTabButton->OnHovered.AddDynamic(this, &UInventory::OnHoveredEquipmentTabButton);
		EquipmentTabButton->OnUnhovered.AddDynamic(this, &UInventory::OnUnhoveredEquipmentTabButton);
		EquipmentTabButton->OnClicked.AddDynamic(this, &UInventory::OnClickedEquipmentTabButton);
	}
}

void UInventory::InitConsumableTabButton()
{
	if (ConsumableTabButton)
	{
		ConsumableTabButton->OnHovered.AddDynamic(this, &UInventory::OnHoveredConsumableTabButton);
		ConsumableTabButton->OnUnhovered.AddDynamic(this, &UInventory::OnUnhoveredConsumableTabButton);
		ConsumableTabButton->OnClicked.AddDynamic(this, &UInventory::OnClickedConsumableTabButton);
	}
}

void UInventory::InitExitButton()
{
	if (ExitButton)
	{
		ExitButton->OnHovered.AddDynamic(this, &UInventory::OnHoveredExitButton);
		ExitButton->OnUnhovered.AddDynamic(this, &UInventory::OnUnhoveredExitButton);
		ExitButton->OnClicked.AddDynamic(this, &UInventory::OnClickedExitButton);
	}
}

void UInventory::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UInventory::SetInGameMenu(UInGameMenu* InInGameMenu)
{
	InGameMenu = InInGameMenu;
}

void UInventory::InitCanvasLocation()
{
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController && InventoryCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& Location = CharacterController->GetInventoryInitialLocation();
			CanvasPanelSlot->SetPosition(Location);
		}
	}
}
