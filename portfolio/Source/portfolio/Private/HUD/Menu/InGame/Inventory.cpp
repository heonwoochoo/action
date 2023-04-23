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
#include "Component/InventoryComponent.h"
#include "HUD/Menu/InGame/ItemBox.h"
#include "HUD/HUDBase.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	InitEquipmentTabButton();
	InitConsumableTabButton();

	InitCanvasLocation();

	ShowItemList(EItemType::EIT_Consumable);
}

void UInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventory::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventory::OnReleasedTitleDragButton()
{
	Super::OnReleasedTitleDragButton();

	// 위치저장
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& CurrentLocation = CanvasPanelSlot->GetPosition();
			CharacterController->SetInventoryInitialLocation(CurrentLocation);

			float PanelSlotSizeX = CanvasPanelSlot->GetSize().X;
			TooltipLocation = FVector2D(CurrentLocation.X + PanelSlotSizeX + 10.f, CurrentLocation.Y + 30.f);
		}
	}
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

void UInventory::ShowItemList(EItemType ItemType)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		const auto& ItemList =  InventoryComponent->GetItemList();
		for (const auto& Item : ItemList)
		{
			UDataTable* SpecData = InventoryComponent->GetItemDataTable();
			if (SpecData)
			{
				const FName& ItemName = Item.Key;
				FItemSpec* Spec = SpecData->FindRow<FItemSpec>(ItemName, "");
				if (Spec)
				{
					if (ItemRow1->GetChildrenCount() < 4)
					{
						UItemBox* ItemBox = Cast<UItemBox>(CreateWidget(this, ItemBoxClass));
						if (ItemBox)
						{
							ItemBox->SetItemName(ItemName);
							ItemBox->SetItemImage(Spec->Image);
							ItemBox->SetItemAmount(Item.Value);
							ItemBox->SetInventory(this);
							ItemRow1->AddChildToHorizontalBox(ItemBox);
						}
					}
				}
			}
		}
	}
}

void UInventory::SetInGameMenu(UInGameMenu* InInGameMenu)
{
	InGameMenu = InInGameMenu;
}

void UInventory::InitCanvasLocation()
{
	Super::InitCanvasLocation();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController && InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& Location = CharacterController->GetInventoryInitialLocation();
			CanvasPanelSlot->SetPosition(Location);

			float PanelSlotSizeX = CanvasPanelSlot->GetSize().X;
			TooltipLocation = FVector2D(Location.X + PanelSlotSizeX + 10.f, Location.Y + 30.f);
		}
	}
}
