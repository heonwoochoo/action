// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DefaultCharacter.h"
#include "Component/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Menu/InGame/CharacterInfo.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	InitEquipmentButton();

	if (EquipmentSlotImage)
	{
		EquipmentSlotImage->SetBrushFromTexture(UnequippedSlot);
	}
}

void UEquipmentSlot::OnHoveredEquipmentButton()
{
	if (CharacterInfo && ItemCode != FName())
	{
		CharacterInfo->OnHoveredSlot(ItemCode);
	}
}

void UEquipmentSlot::OnUnhoveredEquipmentButton()
{
	if (CharacterInfo && ItemCode != FName())
	{
		CharacterInfo->OnUnhoveredSlot();
	}
}

void UEquipmentSlot::InitEquipmentButton()
{
	if (EquipmentButton)
	{
		EquipmentButton->OnHovered.AddDynamic(this, &UEquipmentSlot::OnHoveredEquipmentButton);
		EquipmentButton->OnUnhovered.AddDynamic(this, &UEquipmentSlot::OnUnhoveredEquipmentButton);
	}
}

void UEquipmentSlot::InitByType(EEquipmentType Type)
{
	EquipmentType = Type;

	if (EquipmentImage &&
		HelmetIcon &&
		ArmourIcon &&
		WeaponIcon &&
		SubWeaponIcon &&
		ShieldIcon &&
		AccessoryIcon &&
		ShoesIcon)
	{
		switch (EquipmentType)
		{
		case EEquipmentType::EET_Accessory:
			EquipmentImage->SetBrushFromTexture(AccessoryIcon);
			break;
		case EEquipmentType::EET_Armour:
			EquipmentImage->SetBrushFromTexture(ArmourIcon);
			break;
		case EEquipmentType::EET_Helmet:
			EquipmentImage->SetBrushFromTexture(HelmetIcon);
			break;
		case EEquipmentType::EET_Shield:
			EquipmentImage->SetBrushFromTexture(ShieldIcon);
			break;
		case EEquipmentType::EET_Shoes:
			EquipmentImage->SetBrushFromTexture(ShoesIcon);
			break;
		case EEquipmentType::EET_SubWeapon:
			EquipmentImage->SetBrushFromTexture(SubWeaponIcon);
			break;
		case EEquipmentType::EET_Weapon:
			EquipmentImage->SetBrushFromTexture(WeaponIcon);
			break;
		}
	}
}

void UEquipmentSlot::UpdateSlot()
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter && EquipmentSlotImage && EquipmentImage)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		const TMap<EEquipmentType, FEquippedItem>& EquippedItemList = InventoryComponent->GetEquippedItemList();
		for (const auto& EquippedItem : EquippedItemList)
		{
			const EEquipmentType TargetEquipmentType = EquippedItem.Key;
			const EEquippedState TargetEquippedState = EquippedItem.Value.State;
			if (TargetEquipmentType == EquipmentType && TargetEquippedState == EEquippedState::EES_Equipped)
			{
				ItemCode = EquippedItem.Value.ItemCode;

				UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
				if (ItemSpecData)
				{
					FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
					if (Spec)
					{
						EquipmentSlotImage->SetBrushFromTexture(EquippedSlot);
						EquipmentImage->SetBrushFromTexture(Spec->Image);
					}
				}
			}
		}
	}
}
