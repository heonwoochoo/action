// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/Inventory.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"

void UInventory::NativeConstruct()
{
	InitInventoryDragButton();
	InitEquipmentTabButton();
	InitConsumableTabButton();
	InitExitButton();
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
}

void UInventory::OnReleasedInventoryDragButton()
{
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
