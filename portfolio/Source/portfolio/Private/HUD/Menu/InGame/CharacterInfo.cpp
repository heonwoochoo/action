// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/CharacterInfo.h"
#include "HUD/Menu/InGame/EquipmentSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Controller/CharacterController.h"

void UCharacterInfo::NativeConstruct()
{
	Super::NativeConstruct();

	InitEquipmentSlot();
	InitCanvasLocation();
}

void UCharacterInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCharacterInfo::NativeDestruct()
{
	Super::NativeDestruct();
}



void UCharacterInfo::OnReleasedTitleDragButton()
{
	Super::OnReleasedTitleDragButton();
}

void UCharacterInfo::InitCanvasLocation()
{
	Super::InitCanvasLocation();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController && InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& Location = CharacterController->GetInventoryInitialLocation();
			CanvasPanelSlot->SetPosition(Location);

			float PanelSlotSizeX = CanvasPanelSlot->GetSize().X;
			TooltipLocation = FVector2D(Location.X + PanelSlotSizeX + 10.f, Location.Y + 30.f);
		}
	}
}

void UCharacterInfo::InitEquipmentSlot()
{
	if (HelmetSlot && ArmourSlot && WeaponSlot && SubWeaponSlot && ShieldSlot && AccessorySlot && ShoesSlot)
	{
		HelmetSlot->InitByType(EEquipmentType::EET_Helmet);
		ArmourSlot->InitByType(EEquipmentType::EET_Armour);
		WeaponSlot->InitByType(EEquipmentType::EET_Weapon);
		SubWeaponSlot->InitByType(EEquipmentType::EET_SubWeapon);
		ShieldSlot->InitByType(EEquipmentType::EET_Shield);
		AccessorySlot->InitByType(EEquipmentType::EET_Accessory);
		ShoesSlot->InitByType(EEquipmentType::EET_Shoes);
	}
}
