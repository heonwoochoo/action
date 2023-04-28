// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/ItemSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Component/InventoryComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/ProgressBar.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemSlot::OnUsedItem(const FName& UsedItemCode, const FItemSpec& Spec)
{
	if (UsedItemCode.ToString() == ItemCode.ToString())
	{
		int32 UIAmount = UKismetStringLibrary::Conv_StringToInt(ItemAmount->GetText().ToString());
		if (UIAmount == 1)
		{
			Reset();
		}
		else if (UIAmount > 1)
		{
			int32 NewAmount = UIAmount - 1;
			ItemAmount->SetText(FText::FromString(FString::FromInt(NewAmount)));
		}
	}
}

void UItemSlot::OnAddedItem(const FName& AddedItemCode, const FItemSpec& Spec)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			const TArray<FName>& SlotArray = InventoryComponent->GetItemSlots();
			
			int32 Index = (uint8)SlotNumber;
			if (ItemCode != SlotArray[Index] && SlotArray[Index].IsValid())
			{
				// 새로등록
				ItemCode = AddedItemCode;
			}
			UpdateUI();
		}
	}
}

void UItemSlot::UpdateCoolDownSlot(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		CoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		CoolDownProgressBar->SetPercent(Remaining / Rate);
	}
}

void UItemSlot::ResetCoolDownSlot()
{
	CoolDownText->SetText(FText::GetEmpty());
	CoolDownProgressBar->SetPercent(0.f);
}

void UItemSlot::Reset()
{
	if (ItemAmount && Image)
	{
		ItemAmount->SetText(FText());
		Image->SetBrushFromTexture(nullptr);
		Image->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f));
	}
	PrevItemCode = ItemCode;
	ItemCode = FName();
}

void UItemSlot::UpdateUI()
{
	if (ItemCode == FName()) return;

	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			const TMap<FName, uint8>& ItemList = InventoryComponent->GetItemList();

			UDataTable* ItemTable = InventoryComponent->GetItemDataTable();
			if (ItemTable && ItemList.Contains(ItemCode))
			{
				FItemSpec* Spec = ItemTable->FindRow<FItemSpec>(ItemCode, "");
				if (Spec)
				{
					FText Amount = FText::FromString(FString::FromInt(ItemList[ItemCode]));
					ItemAmount->SetText(Amount);
					Image->SetBrushFromTexture(Spec->Image);
					Image->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
				}
			}
		}
	}
}

void UItemSlot::Init()
{
	const TArray<FString>& KeyArray = { FString(TEXT("Ins")),FString(TEXT("Home")) ,FString(TEXT("Up")) ,FString(TEXT("Del")) ,FString(TEXT("End")) ,FString(TEXT("Down")) };
	
	uint8 Index = (uint8)SlotNumber;

	const FString& InputAction = KeyArray[Index];

	InputKey->SetText(FText::FromString(InputAction));
}
