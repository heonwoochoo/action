// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/InfoContainer.h"
#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include "Items/Weapon.h"

UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	InitEquippedItemList();
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetItemConsumableMapping();
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

void UInventoryComponent::EffectConsumable(const FName& ItemCode)
{
	FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");

	EStatTarget Target{};

	const FCharacterStats& Stats = Spec->Stats;

	float AbilityPoint{};

	if (Stats.HP > 0)
	{
		Target = EStatTarget::EST_Health;
		AbilityPoint = Stats.HP;
	}
	else if (Stats.Stamina > 0)
	{
		Target = EStatTarget::EST_Stamina;
		AbilityPoint = Stats.Stamina;
	}

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

void UInventoryComponent::PlayConsumeSound()
{
	if (PotionConsumeSound)
	{
		UGameplayStatics::PlaySound2D(this, PotionConsumeSound);
	}
}

void UInventoryComponent::InitEquippedItemList()
{
	EquippedItemList.Add({ EEquipmentType::EET_Weapon, FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_SubWeapon, FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_Shoes,FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_Shield, FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_Helmet, FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_Armour, FEquippedItem() });
	EquippedItemList.Add({ EEquipmentType::EET_Accessory, FEquippedItem() });
}

TMap<EEquipmentType, FEquippedItem> UInventoryComponent::GetEquippedItemList() const
{
	return EquippedItemList;
}

void UInventoryComponent::EquipItem(const FName& ItemCode)
{
	// 인벤토리에 존재하는지 확인
	const bool Exist = ItemList.Contains(ItemCode);
	if (Exist)
	{
		FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
		
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(GetOwner());
		if (DefaultCharacter)
		{
			// 장착
			EEquipmentType EquipmentType = Spec->EquipmentType;
			EquippedItemList[EquipmentType] = FEquippedItem(EEquippedState::EES_Equipped, ItemCode);
			DefaultCharacter->UpdateEquipmentStat();

			// 무기일 경우 오브젝트 스폰
			if (EquipmentType == EEquipmentType::EET_Weapon && Spec->ItemClass)
			{
				if (EquippedWeapon)
				{
					EquippedWeapon->Destroy();
				}

				EquippedWeapon = Cast<AWeapon>(GetWorld()->SpawnActor(Spec->ItemClass));
				if (EquippedWeapon)
				{
					USkeletalMeshComponent* Mesh = DefaultCharacter->GetMesh();
					EquippedWeapon->AttachMeshToSocket(Mesh, TEXT("RightHandSocket"));
				}
			}
		}
	}
}

TMap<FName, uint8> UInventoryComponent::GetItemList() const
{
	return ItemList;
}

uint8 UInventoryComponent::GetItemAmount(const FName& ItemName)
{
	if (ItemList.Contains(ItemName))
	{
		return ItemList[ItemName];
	}
	return 0;
}

void UInventoryComponent::AddItem(const FName& ItemCode)
{
	if (!ItemSpecData) return;

	FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
	if (ItemSpec)
	{
		if (ItemList.Contains(ItemCode))
		{
			ItemList[ItemCode]++;
		}
		else
		{
			ItemList.Add(ItemCode);
			ItemList[ItemCode] = 1;
		}

		if (ItemSpec->Type == EItemType::EIT_Consumable)
		{
			UpdateConsumableUI();
		}
	}
}

void UInventoryComponent::UseItem(const FName& ItemCode)
{
	if (ItemCode.IsNone() || ItemSpecData == nullptr) return;
	
	FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
	EItemType ItemType = Spec->Type;
	if (ItemType == EItemType::EIT_Consumable)
	{
		// 실제 데이터 적용
		EffectConsumable(ItemCode);

		// 멤버변수의 데이터를 업데이트
		if (ItemList.Contains(ItemCode))
		{
			if (ItemList[ItemCode] == 1)
			{
				ItemList.Remove(ItemCode);
			}
			else ItemList[ItemCode]--;

			UpdateConsumableUI();
		}

		SpawnConsumeParticle(Spec->EffectParticle);

		PlayConsumeSound();
	}
}

UDataTable* UInventoryComponent::GetItemDataTable() const
{
	return ItemSpecData;
}

int32 UInventoryComponent::GetInventorySlotNumber(const EItemType& Type)
{
	switch (Type)
	{
	case EItemType::EIT_Equipment:
		return InventoryEquipmentSlotNumber;
	case EItemType::EIT_Consumable:
		return InventoryConsumableSlotNumber;
	}

	return 0;
}

void UInventoryComponent::UpdateConsumableUI()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
		UInfoContainer* InfoContainer = HUD->GetInfoContainer();
		if (InfoContainer)
		{
			// 순서도 바뀔 수 있으니 업데이트 시켜야함
			ResetItemConsumableMapping();

			InfoContainer->UpdateConsumableQuickSlot();
		}
	}
}

void UInventoryComponent::SlotHandle_1()
{
	if (bEnableItem1 && ItemSpecData && Slot1 != FName())
	{
		bEnableItem1 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot1, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle1, this, &UInventoryComponent::EndTimerHandle1, CoolDown);
		
		UseItem(Slot1);
	}
}

void UInventoryComponent::SlotHandle_2()
{
	if (bEnableItem2 && ItemSpecData && HasItemInContainer(EItemNumber::EIN_2))
	{
		bEnableItem2 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot2, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle2, this, &UInventoryComponent::EndTimerHandle2, CoolDown);

		UseItem(Slot2);
	}
}

void UInventoryComponent::SlotHandle_3()
{
	if (bEnableItem3 && ItemSpecData && HasItemInContainer(EItemNumber::EIN_3))
	{
		bEnableItem3 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot3, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle3, this, &UInventoryComponent::EndTimerHandle3, CoolDown);

		UseItem(Slot3);
	}
}

void UInventoryComponent::SlotHandle_4()
{
	if (bEnableItem4 && ItemSpecData && HasItemInContainer(EItemNumber::EIN_4))
	{
		bEnableItem4 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot4, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle4, this, &UInventoryComponent::EndTimerHandle4, CoolDown);

		UseItem(Slot4);
	}
}

void UInventoryComponent::SlotHandle_5()
{
	if (bEnableItem5 && ItemSpecData && HasItemInContainer(EItemNumber::EIN_5))
	{
		bEnableItem5 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot5, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle5, this, &UInventoryComponent::EndTimerHandle5, CoolDown);

		UseItem(Slot5);
	}
}

void UInventoryComponent::SlotHandle_6()
{
	if (bEnableItem6 && ItemSpecData && HasItemInContainer(EItemNumber::EIN_6))
	{
		bEnableItem6 = false;

		const FItemSpec& ItemSpec = *ItemSpecData->FindRow<FItemSpec>(Slot6, "");
		const float CoolDown = ItemSpec.Stats.CoolDown;

		GetWorld()->GetTimerManager().SetTimer(ItemTimerHandle6, this, &UInventoryComponent::EndTimerHandle6, CoolDown);

		UseItem(Slot6);
	}
}

void UInventoryComponent::ResetItemConsumableMapping()
{
	Slot1 = FName();
	Slot2 = FName();
	Slot3 = FName();
}

void UInventoryComponent::SetItemConsumableMapping(const FName& ItemCode, uint8 Idx)
{
	switch (Idx)
	{
	case 0:
		Slot1 = ItemCode;
		break;
	case 1:
		Slot2 = ItemCode;
		break;
	case 2:
		Slot3 = ItemCode;
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
	FName TargetItem;

	switch (ItemNum)
	{
	case EItemNumber::EIN_1:
		TargetItem = Slot1;
		break;
	case EItemNumber::EIN_2:
		TargetItem = Slot2;
		break;
	case EItemNumber::EIN_3:
		TargetItem = Slot3;
		break;
	case EItemNumber::EIN_4:
		TargetItem = Slot4;
		break;
	case EItemNumber::EIN_5:
		TargetItem = Slot5;
		break;
	case EItemNumber::EIN_6:
		TargetItem = Slot6;
		break;
	}

	return TargetItem != FName();
}

bool UInventoryComponent::IsEquippedItem(FName ItemCode)
{
	for (const auto& EquippedItemMap : EquippedItemList)
	{
		const FEquippedItem& EquippedItem = EquippedItemMap.Value;
		const EEquippedState State = EquippedItem.State;
		const FName Code = EquippedItem.ItemCode;
		if (State == EEquippedState::EES_Equipped && Code == ItemCode)
		{
			return true;
		}
	}
	return false;
}

void UInventoryComponent::SetEquippedItemCode(const FName& ItemCode)
{
	EquippedItemCode = ItemCode;
}

FName UInventoryComponent::GetEquippedItemCode() const
{
	return EquippedItemCode;
}

