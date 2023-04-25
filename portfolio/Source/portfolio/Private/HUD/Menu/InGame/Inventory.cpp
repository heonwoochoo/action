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
#include "Components/TextBlock.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	InitEquipmentTabButton();
	InitConsumableTabButton();
	
	// 탭 이미지 초기 설정
	UncheckTabImage(EItemType::EIT_Equipment);
	UncheckTabImage(EItemType::EIT_Consumable);

	InitCanvasLocation();

	// 오픈시 처음 보여지는 탭 설정
	SelectedTap = EItemType::EIT_Equipment;
	UpdateTabImage(true, EquipmentTabBackground, EquipmentTabText, EquipmentTabUnderline);
	ShowItemList(SelectedTap);
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
	if (SelectedTap != EItemType::EIT_Equipment)
	{
		if (EquipmentTabUnderline)
		{
			EquipmentTabUnderline->SetOpacity(1.f);
		}
	}
}

void UInventory::OnUnhoveredEquipmentTabButton()
{
	if (SelectedTap != EItemType::EIT_Equipment)
	{
		if (EquipmentTabUnderline)
		{
			EquipmentTabUnderline->SetOpacity(0.f);
		}
	}
}

void UInventory::OnClickedEquipmentTabButton()
{
	if (SelectedTap != EItemType::EIT_Equipment)
	{
		UncheckTabImage(SelectedTap);

		UpdateTabImage(true, EquipmentTabBackground, EquipmentTabText, EquipmentTabUnderline);

		SelectedTap = EItemType::EIT_Equipment;

		UpdateItemList(SelectedTap);

		PlayChangeButtonSound();
	}
}

void UInventory::OnHoveredConsumableTabButton()
{
	if (SelectedTap != EItemType::EIT_Consumable)
	{
		if (ConsumableTabUnderline)
		{
			ConsumableTabUnderline->SetOpacity(1.f);
		}
	}
}

void UInventory::OnUnhoveredConsumableTabButton()
{
	if (SelectedTap != EItemType::EIT_Consumable)
	{
		if (ConsumableTabUnderline)
		{
			ConsumableTabUnderline->SetOpacity(0.f);
		}
	}
}

void UInventory::OnClickedConsumableTabButton()
{
	if (SelectedTap != EItemType::EIT_Consumable)
	{
		UncheckTabImage(SelectedTap);

		UpdateTabImage(true, ConsumableTabBackground, ConsumableTabText, ConsumableTabUnderline);
		
		SelectedTap = EItemType::EIT_Consumable;
		
		UpdateItemList(SelectedTap);
		
		PlayChangeButtonSound();
	}
}

void UInventory::UpdateItemList(EItemType ItemType)
{
	ClearAllItemBox();

	ShowItemList(ItemType);
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
				const FName& ItemCode = Item.Key;
				FItemSpec* Spec = SpecData->FindRow<FItemSpec>(ItemCode, "");
				if (Spec && Spec->Type == ItemType)
				{
					const int32 EntireAmount = Item.Value;
					const int32 MaxAmount = Spec->AmountMax;
					const int32 RequiredSlotNumber =
						EntireAmount % MaxAmount ? (EntireAmount / MaxAmount) + 1 : (EntireAmount / MaxAmount);

					for (int32 i = 0; i < RequiredSlotNumber; ++i)
					{
						int32 Amount;
						if (i == RequiredSlotNumber - 1)
						{
							Amount = EntireAmount % MaxAmount;
						}
						else
						{
							Amount = MaxAmount;
						}

						UItemBox* ItemBox = Cast<UItemBox>(CreateWidget(this, ItemBoxClass));
						if (ItemBox)
						{
							ItemBox->SetItemCode(ItemCode);
							ItemBox->SetItemImage(Spec->Image);
							ItemBox->SetItemAmount(Amount);
							ItemBox->SetInventory(this);

							if (ItemRow1->GetChildrenCount() < 4)
							{
								ItemRow1->AddChildToHorizontalBox(ItemBox);
							}
							else if (ItemRow2->GetChildrenCount() < 4)
							{
								ItemRow2->AddChildToHorizontalBox(ItemBox);
							}
							else if (ItemRow3->GetChildrenCount() < 4)
							{
								ItemRow3->AddChildToHorizontalBox(ItemBox);
							}
						}
					}
				}
			}
		}
	}
}

void UInventory::ClearAllItemBox()
{
	ItemRow1->ClearChildren();
	ItemRow2->ClearChildren();
	ItemRow3->ClearChildren();
}

void UInventory::UpdateTabImage(bool IsActive, UImage* TabBackground, UTextBlock* TabText, UImage* TabUnderline)
{
	if (TabBackground == nullptr || TabText == nullptr || TabUnderline == nullptr) return;
	if (IsActive)
	{
		if (ActivatedTab)
		{
			// 배경
			TabBackground->SetBrushFromTexture(ActivatedTab);
		}
		// 글자 투명도
		TabText->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));

		// 폰트 크기
		FSlateFontInfo FontInfo = TabText->GetFont();
		FontInfo.Size = 15;
		TabText->SetFont(FontInfo);

		// 밑줄 투명도
		TabUnderline->SetOpacity(1.f);
	}
	else
	{
		if (DeactivatedTab)
		{
			TabBackground->SetBrushFromTexture(DeactivatedTab);
		}

		TabText->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.3f));

		FSlateFontInfo FontInfo = TabText->GetFont();
		FontInfo.Size = 9;
		TabText->SetFont(FontInfo);
		
		TabUnderline->SetOpacity(0.f);
	}
}

void UInventory::UncheckTabImage(EItemType TargetTab)
{
	switch (TargetTab)
	{
	case EItemType::EIT_Equipment:
		UpdateTabImage(false, EquipmentTabBackground, EquipmentTabText, EquipmentTabUnderline);
		break;
	case EItemType::EIT_Consumable:
		UpdateTabImage(false, ConsumableTabBackground, ConsumableTabText, ConsumableTabUnderline);
		break;
	}
}

void UInventory::PlayChangeButtonSound()
{
	 ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	 if (DefaultGameMode)
	 {
		 DefaultGameMode->PlayChangeButtonClickSound();
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
