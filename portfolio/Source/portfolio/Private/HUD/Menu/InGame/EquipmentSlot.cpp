// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/EquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (EquipmentSlotImage)
	{
		EquipmentSlotImage->SetBrushFromTexture(UnequippedSlot);
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
