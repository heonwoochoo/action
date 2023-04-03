// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello Inventory"));
	
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

uint8 UInventoryComponent::GetItemAmount(EItemName ItemName)
{
	if (ItemsAmount.Contains(ItemName))
	{
		return ItemsAmount[ItemName];
	}
	else return 0;
}

void UInventoryComponent::AddItem(EItemName ItemName)
{
	if (ItemsAmount.Contains(ItemName))
	{
		FName RowName;
		switch (ItemName)
		{
		case EItemName::EIN_HealthPotion:
			RowName = "HealthPotion";
			break;
		case EItemName::EIN_StaminaPotion:
			RowName = "StaminaPotion";
			break;
		default:
			break;
		}
		uint8 AmountMax = PotionDataTable->FindRow<FPotionInfo>(RowName, "")->AmountMax;
		if (ItemsAmount[ItemName] < AmountMax)
		{
			ItemsAmount[ItemName]++;
		}
	}
	else
	{
		ItemsAmount[ItemName] = 1;
	}
}

void UInventoryComponent::UseItem(EItemName ItemName)
{
	if (ItemsAmount.Contains(ItemName))
	{
		if (ItemsAmount[ItemName] == 1)
		{
			ItemsAmount.Remove(ItemName);
		}
		else ItemsAmount[ItemName]--;
	}
}

