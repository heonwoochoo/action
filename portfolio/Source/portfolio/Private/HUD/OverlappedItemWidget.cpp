// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/OverlappedItemWidget.h"
#include "Items/Potion.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UOverlappedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOverlappedItemWidget::UpdateOverlappedItemInfo(AActor* Item)
{
	if (Item->ActorHasTag(FName("Potion")))
	{
		APotion* Potion = Cast<APotion>(Item);
		
		if (Potion)
		{
			if (ItemImage && ItemName && ItemDescription && ItemCoolDown)
			{
				// 이미지
				ItemImage->SetBrushFromTexture(Potion->GetImage());
				// 이름
				ItemName->SetText(FText::FromName(Potion->GetName()));
				// 정보
				ItemDescription->SetText(FText::FromName(Potion->GetDescription()));
				// 쿨다운
				ItemCoolDown->SetText(FText::FromString(FString::SanitizeFloat(Potion->GetCoolDown())));
			}
		}
	}
}
