// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverlappedItemWidget.h"
#include "Items/Potion.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"

void UOverlappedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOverlappedItemWidget::UpdateOverlappedItemInfo(AItemBase* Item)
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
