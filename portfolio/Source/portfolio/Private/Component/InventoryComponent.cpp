// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/InfoContainer.h"
#include "DefaultCharacter.h"

UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetItemPotionMapping();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UInventoryComponent::EffectPotion(EStatTarget Target, float CoolDown, float AbilityPoint)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		DefaultCharacter->UpdateStatManager(Target, EStatUpdateType::ESUT_Plus, AbilityPoint);
	}
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
	if (ItemName == EItemName::EIN_None) return;

	// 실제 데이터 적용
	// 데이터테이블로부터 이펙트타겟, 쿨타임, 포인트 받아오기
	if (!PotionDataTable) return;
	FName RowName;
	switch (ItemName)
	{
	case EItemName::EIN_HealthPotion:
		RowName = "HealthPotion";
		break;
	case EItemName::EIN_StaminaPotion:
		RowName = "StaminaPotion";
		break;
	}
	FPotionInfo* PotionInfo = PotionDataTable->FindRow<FPotionInfo>(RowName, "");
	if (!PotionInfo) return;

	EStatTarget Target = PotionInfo->StatTarget;
	float CoolDown = PotionInfo->CoolDown;
	float AbilityPoint = PotionInfo->AbilityPoint;

	// 캐릭터에 적용
	EffectPotion(Target, CoolDown, AbilityPoint);


	// 멤버변수의 데이터를 업데이트
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

void UInventoryComponent::ItemHandle_1()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 1"));
	UseItemPotion(Item1);
}

void UInventoryComponent::ItemHandle_2()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 2"));
	UseItemPotion(Item2);
}

void UInventoryComponent::ItemHandle_3()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 3"));
	UseItemPotion(Item3);
}

void UInventoryComponent::ItemHandle_4()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 4"));
}

void UInventoryComponent::ItemHandle_5()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 5"));
}

void UInventoryComponent::ItemHandle_6()
{
	UE_LOG(LogTemp, Warning, TEXT("Handle 6"));
}

void UInventoryComponent::ResetItemPotionMapping()
{
	Item1 = EItemName::EIN_None;
	Item2 = EItemName::EIN_None;
	Item3 = EItemName::EIN_None;
}

void UInventoryComponent::SetItemPotionMapping(EItemName Name, uint8 Idx)
{
	switch (Idx)
	{
	case 0:
		Item1 = Name;
	case 1:
		Item2 = Name;
	case 2:
		Item3 = Name;
	}
}

