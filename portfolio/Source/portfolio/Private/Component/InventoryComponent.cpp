// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/InfoContainer.h"
#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"

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

void UInventoryComponent::EndTimerHandle1()
{
	bEnableItem1 = true;
}

void UInventoryComponent::EndTimerHandle2()
{
	bEnableItem2 = true;
}

void UInventoryComponent::EndTimerHandle3()
{
	bEnableItem3 = true;
}

void UInventoryComponent::EndTimerHandle4()
{
	bEnableItem4 = true;
}

void UInventoryComponent::EndTimerHandle5()
{
	bEnableItem5 = true;
}

void UInventoryComponent::EndTimerHandle6()
{
	bEnableItem6 = true;
}

void UInventoryComponent::EffectPotion(EStatTarget Target, float CoolDown, float AbilityPoint)
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		DefaultCharacter->UpdateStatManager(Target, EStatUpdateType::ESUT_Plus, AbilityPoint);
	}
}

void UInventoryComponent::SpawnConsumeParticle(UParticleSystem* Particle)
{
	if (Particle)
	{
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (DefaultCharacter)
		{
			USceneComponent* AttachedComponent = Cast<USceneComponent>(DefaultCharacter->GetCapsuleComponent());
			UGameplayStatics::SpawnEmitterAttached(Particle, AttachedComponent);
		}
	}
}

float UInventoryComponent::GetItemPotionCoolDown(EItemName Name)
{
	if (PotionDataTable)
	{
		FName RowName;
		switch (Name)
		{
		case EItemName::EIN_HealthPotion:
			RowName = "HealthPotion";
			break;
		case EItemName::EIN_StaminaPotion:
			RowName = "StaminaPotion";
			break;
		}
		FPotionInfo* PotionInfo = PotionDataTable->FindRow<FPotionInfo>(RowName, "");
		if (PotionInfo)
		{
			return PotionInfo->CoolDown;
		}
	}
	return 0.0f;
}

void UInventoryComponent::PlayConsumeSound()
{
	if (PotionConsumeSound)
	{
		UGameplayStatics::PlaySound2D(this, PotionConsumeSound);
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
	const float CoolDown = PotionInfo->CoolDown;
	const float AbilityPoint = PotionInfo->AbilityPoint;

	EffectPotion(Target, CoolDown, AbilityPoint);

	SpawnConsumeParticle(PotionInfo->ConsumeParticle);

	PlayConsumeSound();

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
	if (bEnableItem1 && HasItemInContainer(EItemNumber::EIN_1))
	{
		bEnableItem1 = false;
		const float CoolDown = GetItemPotionCoolDown(Item1);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle1, this, &UInventoryComponent::EndTimerHandle1, CoolDown);
		UseItemPotion(Item1);
	}
}

void UInventoryComponent::ItemHandle_2()
{
	if (bEnableItem2 && HasItemInContainer(EItemNumber::EIN_2))
	{
		bEnableItem2 = false;
		const float CoolDown = GetItemPotionCoolDown(Item2);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle2, this, &UInventoryComponent::EndTimerHandle2, CoolDown);
		UseItemPotion(Item2);
	}
}

void UInventoryComponent::ItemHandle_3()
{
	if (bEnableItem3 && HasItemInContainer(EItemNumber::EIN_3))
	{
		bEnableItem3 = false;
		const float CoolDown = GetItemPotionCoolDown(Item3);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle3, this, &UInventoryComponent::EndTimerHandle3, CoolDown);
		UseItemPotion(Item3);
	}
}

void UInventoryComponent::ItemHandle_4()
{
	if (bEnableItem4 && HasItemInContainer(EItemNumber::EIN_4))
	{
		bEnableItem4 = false;
		const float CoolDown = GetItemPotionCoolDown(Item4);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle4, this, &UInventoryComponent::EndTimerHandle4, CoolDown);
		UseItemPotion(Item4);
	}
}

void UInventoryComponent::ItemHandle_5()
{
	if (bEnableItem5 && HasItemInContainer(EItemNumber::EIN_5))
	{
		bEnableItem5 = false;
		const float CoolDown = GetItemPotionCoolDown(Item5);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle5, this, &UInventoryComponent::EndTimerHandle5, CoolDown);
		UseItemPotion(Item5);
	}
}

void UInventoryComponent::ItemHandle_6()
{
	if (bEnableItem6 && HasItemInContainer(EItemNumber::EIN_6))
	{
		bEnableItem6 = false;
		const float CoolDown = GetItemPotionCoolDown(Item6);
		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle6, this, &UInventoryComponent::EndTimerHandle6, CoolDown);
		UseItemPotion(Item6);
	}
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
		break;
	case 1:
		Item2 = Name;
		break;
	case 2:
		Item3 = Name;
		break;
	}
}

FTimerHandle* UInventoryComponent::GetItemTimerHandle(EItemNumber ItemNum)
{
	FTimerHandle* TimerHandle = nullptr;

	switch (ItemNum)
	{
	case EItemNumber::EIN_1:
		TimerHandle = &ItemTimerHandle1;
		break;
	case EItemNumber::EIN_2:
		TimerHandle = &ItemTimerHandle2;
		break;
	case EItemNumber::EIN_3:
		TimerHandle = &ItemTimerHandle3;
		break;
	case EItemNumber::EIN_4:
		TimerHandle = &ItemTimerHandle4;
		break;
	case EItemNumber::EIN_5:
		TimerHandle = &ItemTimerHandle5;
		break;
	case EItemNumber::EIN_6:
		TimerHandle = &ItemTimerHandle6;
		break;
	}

	return TimerHandle;
}

bool UInventoryComponent::GetEnableItem(EItemNumber ItemNum)
{
	bool EnableItem = false;

	switch (ItemNum)
	{
	case EItemNumber::EIN_1:
		EnableItem = bEnableItem1;
		break;
	case EItemNumber::EIN_2:
		EnableItem = bEnableItem2;
		break;
	case EItemNumber::EIN_3:
		EnableItem = bEnableItem3;
		break;
	case EItemNumber::EIN_4:
		EnableItem = bEnableItem4;
		break;
	case EItemNumber::EIN_5:
		EnableItem = bEnableItem5;
		break;
	case EItemNumber::EIN_6:
		EnableItem = bEnableItem6;
		break;
	}

	return EnableItem;
}

bool UInventoryComponent::HasItemInContainer(EItemNumber ItemNum)
{
	EItemName TargetItem = EItemName::EIN_None;

	switch (ItemNum)
	{
	case EItemNumber::EIN_1:
		TargetItem = Item1;
		break;
	case EItemNumber::EIN_2:
		TargetItem = Item2;
		break;
	case EItemNumber::EIN_3:
		TargetItem = Item3;
		break;
	case EItemNumber::EIN_4:
		TargetItem = Item4;
		break;
	case EItemNumber::EIN_5:
		TargetItem = Item5;
		break;
	case EItemNumber::EIN_6:
		TargetItem = Item6;
		break;
	}

	return TargetItem != EItemName::EIN_None;
}

