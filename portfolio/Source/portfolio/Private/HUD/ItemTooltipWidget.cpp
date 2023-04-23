﻿// Fill out your copyright notice in the Description page of Project Settings.


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

void UItemTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemTooltipWidget::NativeDestruct()
{
	UE_LOG(LogTemp, Warning, TEXT("Item tooltip Destruct"));
}

void UItemTooltipWidget::UpdateContents(const FName& InItemName)
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
				FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(InItemName, "");
				// 이미지
				ItemImage->SetBrushFromTexture(Spec->Image);
				// 이름
				ItemName->SetText(FText::FromName(InItemName));
				// 정보
				ItemDescription->SetText(FText::FromName(Spec->Description));
				// 쿨다운
				ItemCoolDown->SetText(FText::FromString(FString::SanitizeFloat(Spec->Stats.CoolDown)));
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
