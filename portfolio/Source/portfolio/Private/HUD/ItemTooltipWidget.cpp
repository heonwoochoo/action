// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ItemTooltipWidget.h"
#include "Items/Potion.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"
#include "Component/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Types/ItemTypes.h"
#include "Components/HorizontalBox.h"

void UItemTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
void UItemTooltipWidget::UpdateContents(const FName& ItemCode)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
			if (ItemSpecData)
			{
				FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
				// 이미지
				ItemImage->SetBrushFromTexture(Spec->Image);
				
				// 이름
				ItemName->SetText(FText::FromName(Spec->Name));
				
				// 설명
				ItemDescription->SetText(FText::FromName(Spec->Description));
				
				// 등급
				const EItemRarity Rarity = Spec->Rarity;
				FText RarityText{};
				FColor TextColor{};
				switch (Rarity)
				{
				case EItemRarity::EIR_Normal:
					RarityText = FText::FromString(TEXT("노멀"));
					TextColor = FColor::White;
					break;
				case EItemRarity::EIR_Rare:
					RarityText = FText::FromString(TEXT("레어"));
					TextColor = FColor::Purple;
					break;
				case EItemRarity::EIR_Unique:
					RarityText = FText::FromString(TEXT("유니크"));
					TextColor = FColor::Magenta;
					break;
				case EItemRarity::EIR_Epic:
					RarityText = FText::FromString(TEXT("에픽"));
					TextColor = FColor::Yellow;
					break;
				}
				ItemRarityText->SetText(RarityText);
				ItemRarityText->SetColorAndOpacity(TextColor);

				// 타입별 나타낼 정보
				const EItemType ItemType = Spec->Type;
				if (ItemType == EItemType::EIT_Consumable)
				{
					ItemTypeText->SetText(FText::FromString(TEXT("소모품")));
					EquipmentNotifyBox->SetVisibility(ESlateVisibility::Hidden);
					ConsumableNotifyBox->SetVisibility(ESlateVisibility::Visible);
					// 쿨다운
					ItemCoolDown->SetText(FText::FromString(FString::SanitizeFloat(Spec->Stats.CoolDown)));
				}
				else if (ItemType == EItemType::EIT_Equipment)
				{
					const FText& EquipmentTypeText = GetEquipmentTypeText(ItemCode);
					ItemTypeText->SetText(EquipmentTypeText);
					EquipmentNotifyBox->SetVisibility(ESlateVisibility::Visible);
					ConsumableNotifyBox->SetVisibility(ESlateVisibility::Hidden);

					// 장착 상태에 따라 표기
					const bool IsEquipped = InventoryComponent->IsEquippedItem(ItemCode);
					if (IsEquipped)
					{
						EquippedStateText->SetText(FText::FromString(TEXT("장착중")));
					}
					else
					{
						EquippedStateText->SetText(FText::FromString(TEXT("")));
					}
				}
			}
		}
	}
}

void UItemTooltipWidget::SetCanvasPosition(const FVector2D& Location)
{
	if (ItemCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemCanvas);
		if (CanvasPanelSlot)
		{
			//CanvasPanelSlot->SetDesiredPosition(Location);
			CanvasPanelSlot->SetPosition(Location);
		}
	}
}

FVector2D UItemTooltipWidget::GetCanvasSize() const
{
	if (ItemCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemCanvas);
		if (CanvasPanelSlot)
		{
			return CanvasPanelSlot->GetSize();
		}
	}
	return FVector2D();
}

FText UItemTooltipWidget::GetEquipmentTypeText(const FName& ItemCode)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
			if (ItemSpecData)
			{
				FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
				if (Spec)
				{
					const EEquipmentType EquipmentType = Spec->EquipmentType;
					FText ResultText{};
					switch (EquipmentType)
					{
					case EEquipmentType::EET_Weapon:
						ResultText = FText::FromString(TEXT("한손검"));
						break;
					case EEquipmentType::EET_SubWeapon:
						ResultText = FText::FromString(TEXT("보조무기"));
						break;
					case EEquipmentType::EET_Shoes:
						ResultText = FText::FromString(TEXT("신발"));
						break;
					case EEquipmentType::EET_Shield:
						ResultText = FText::FromString(TEXT("방패"));
						break;
					case EEquipmentType::EET_Helmet:
						ResultText = FText::FromString(TEXT("투구"));
						break;
					case EEquipmentType::EET_Armour:
						ResultText = FText::FromString(TEXT("갑옷"));
						break;
					case EEquipmentType::EET_Accessory:
						ResultText = FText::FromString(TEXT("장신구"));
						break;
					default:
						ResultText = FText::FromString(TEXT("미정"));
						break;
					}
					return ResultText;
				}
			}
		}
	}
	return FText();
}
