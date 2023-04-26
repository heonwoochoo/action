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
#include "GameMode/DefaultGameMode.h"
#include "DefaultCharacter.h"
#include "Component/InventoryComponent.h"
#include "Types/ItemTypes.h"
#include "Animation/AnimInstanceBase.h"

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
				const FCharacterStats& Stats = DefaultCharacter->GetCharacterStats();
				const int32 CharacterLevel = Stats.Level;
				const int32 ItemLevel = Spec->Stats.Level;
				// 레벨 확인
				if (CharacterLevel >= ItemLevel)
				{
					EItemType ItemType = Spec->Type;

					switch (ItemType)
					{
					case EItemType::EIT_Equipment:
						if (IsEquipped(ItemCode))
						{
							// 이미 장착 중
						}
						else
						{
							InventoryComponent->SetEquippedItemCode(ItemCode);
							PlayEquipAnimation();
						}
						break;
					case EItemType::EIT_Consumable:
						InventoryComponent->UseItem(ItemCode);
						Inventory->UpdateItemList(ItemType);
						break;
					}
				}
				else
				{
					// 유저 메세지 출력
					ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
					if (CharacterController)
					{
						AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
						if (HUDBase)
						{
							const FText Message = FText::FromString(TEXT("유저의 레벨이 낮아 해당 장비를 착용할 수 없습니다."));
							HUDBase->NotifyMessageToUser(Message);
						}
					}
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

void UItemBox::PlayEquipAnimation()
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		USkeletalMeshComponent* Mesh = DefaultCharacter->GetMesh();
		if (Mesh)
		{
			UAnimInstanceBase* AnimInstance = Cast<UAnimInstanceBase>(Mesh->GetAnimInstance());
			if (AnimInstance)
			{
				AnimInstance->PlayEquipWeapon();
			}
		}
	}
}

bool UItemBox::IsEquipped(const FName& TargetItemCode)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			const TMap<EEquipmentType, FEquippedItem>& EquippedItemList = InventoryComponent->GetEquippedItemList();
			for (const auto& EquippedItem : EquippedItemList)
			{
				const FEquippedItem& Item = EquippedItem.Value;
				const FName& EquippedItemCode = Item.ItemCode;
				if (EquippedItemCode == TargetItemCode)
				{
					// 유저 메세지 출력
					ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
					if (CharacterController)
					{
						AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
						if (HUDBase)
						{
							const FText Message = FText::FromString(TEXT("이미 장착 중인 아이템입니다."));
							HUDBase->NotifyMessageToUser(Message);
						}
					}
					return true;
				}
			}
		}
	}

	return false;
}