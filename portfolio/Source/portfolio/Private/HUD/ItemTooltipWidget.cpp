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

void UItemTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemTooltipWidget::UpdateOverlappedItemInfo(AItemBase* Item)
{
	if (Item->ActorHasTag(FName("Item")))
	{
		const FItemSpec& Spec = Item->GetItemSpec();

		// 이미지
		ItemImage->SetBrushFromTexture(Spec.Image);
		// 이름
		ItemName->SetText(FText::FromName(Spec.Name));
		// 정보
		ItemDescription->SetText(FText::FromName(Spec.Description));
		// 쿨다운
		ItemCoolDown->SetText(FText::FromString(FString::SanitizeFloat(Spec.Stats.CoolDown)));
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
