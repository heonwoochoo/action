// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ItemBox.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "HUD/ItemTooltipWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "HUD/Menu/InGame/Inventory.h"

void UItemBox::NativeConstruct()
{
	InitItemBoxButton();
}

void UItemBox::OnHoveredItemBoxButton()
{
	if (ItemSlotImage)
	{
		ItemSlotImage->SetBrushTintColor(FLinearColor(0.1f, 0.1f, 0.1f));
	}

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase && ItemName != FName() && Inventory)
		{
			const FVector2D& TooltipLocation = Inventory->GetTooltipLocation();
			HUDBase->ShowItemTooltip(ItemName, TooltipLocation);
		}
	}
}

void UItemBox::OnUnhoveredItemBoxButton()
{
	
	if (ItemSlotImage)
	{
		ItemSlotImage->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f));
	}

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->HideItemTooltip();
		}
	}
}

void UItemBox::OnClickedItemBoxButton()
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

void UItemBox::InitItemBoxButton()
{
	if (ItemBoxButton)
	{
		ItemBoxButton->OnHovered.AddDynamic(this, &UItemBox::OnHoveredItemBoxButton);
		ItemBoxButton->OnUnhovered.AddDynamic(this, &UItemBox::OnUnhoveredItemBoxButton);
		ItemBoxButton->OnClicked.AddDynamic(this, &UItemBox::OnClickedItemBoxButton);
	}
}