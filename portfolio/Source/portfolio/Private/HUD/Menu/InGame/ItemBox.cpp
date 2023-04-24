﻿// Fill out your copyright notice in the Description page of Project Settings.


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
#include "GameMode/DefaultGameMode.h"
#include "DefaultCharacter.h"
#include "Component/InventoryComponent.h"
#include "Types/ItemTypes.h"

void UItemBox::NativeConstruct()
{

}

FReply UItemBox::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
			if (ItemSpecData && ItemCode.IsValid())
			{
				FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
				
				EItemType ItemType = Spec->Type;
				
				switch (ItemType)
				{
				case EItemType::EIT_Equipment:
					UE_LOG(LogTemp, Warning, TEXT("장비 장착"));
					break;
				case EItemType::EIT_Consumable:
					UE_LOG(LogTemp, Warning, TEXT("소모품 사용"));
					InventoryComponent->UseItem(ItemCode);
					Inventory->UpdateItemList(ItemType);
					break;
				}
			}
		}
	}

	return FReply::Handled();
}

void UItemBox::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);


	if (ItemSlotImage)
	{
		ItemSlotImage->SetBrushTintColor(FLinearColor(0.1f, 0.1f, 0.1f));
	}

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase && ItemCode != FName() && Inventory)
		{
			const FVector2D& TooltipLocation = Inventory->GetTooltipLocation();
			HUDBase->ShowItemTooltip(ItemCode, TooltipLocation);
		}
	}
}

void UItemBox::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

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