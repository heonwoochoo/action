// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ItemBox.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemBox::NativeConstruct()
{
}

void UItemBox::SetItemImage(UTexture2D* Image)
{
	if (Image && ItemImage)
	{
		ItemImage->SetBrushFromTexture(Image);
	}
}

void UItemBox::SetItemAmount(uint8 Amount)
{
	if (ItemAmount && Amount > 0)
	{
		ItemAmount->SetText(FText::FromString(FString::FromInt(Amount)));
	}
}
