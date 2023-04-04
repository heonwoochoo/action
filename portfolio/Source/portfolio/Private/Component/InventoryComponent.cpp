// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/InfoContainer.h"

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

TMap<EItemName, uint8> UInventoryComponent::GetItemAmountMap() const
{
	return ItemsAmount;
}

uint8 UInventoryComponent::GetItemAmount(EItemName ItemName)
{
	if (ItemsAmount.Contains(ItemName))
	{
		return ItemsAmount[ItemName];
	}
	else return 0;
}

void UInventoryComponent::AddItemPotion(EItemName ItemName)
{
	if (!PotionDataTable) return;
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
		// 최대로 가질 수 있는 아이템의 종류는 6가지입니다.
		if (ItemsAmount.Num() == 6) return;

		ItemsAmount.Add({ ItemName, 1 });
	}

	UpdatePotionUI();
}

void UInventoryComponent::UseItemPotion(EItemName ItemName)
{
	if (ItemsAmount.Contains(ItemName))
	{
		if (ItemsAmount[ItemName] == 1)
		{
			ItemsAmount.Remove(ItemName);
		}
		else ItemsAmount[ItemName]--;

		UpdatePotionUI();
	}
}

UDataTable* UInventoryComponent::GetPotionDataTable() const
{
	return PotionDataTable;
}

void UInventoryComponent::UpdatePotionUI()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
		UInfoContainer* InfoContainer = HUD->GetInfoContainer();
		if (InfoContainer)
		{
			InfoContainer->UpdatePotionInventory();
		}
	}
}

