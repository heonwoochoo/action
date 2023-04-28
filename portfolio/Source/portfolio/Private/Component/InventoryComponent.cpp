// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/InfoContainer.h"
#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include "Items/Weapon.h"
#include "Controller/CharacterController.h"

UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	InitEquippedItemList();
}

void UInventoryComponent::NotifyCoolDown(const FTimerHandle& TimerHandle, const FOnProgressCoolDownSignature& Delegate)
{
	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	const float& Remaining = TimerManager.GetTimerRemaining(TimerHandle);
	const float& Rate = TimerManager.GetTimerRate(TimerHandle);

	Delegate.Broadcast(Remaining, Rate);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleItemSlotCoolDown();
}

void UInventoryComponent::EndSlotOneTimerHandle()
{
	bEnableItemSlotOne = true;
	OnEndCoolDownSlotOne.Broadcast();
}

void UInventoryComponent::EndSlotTwoTimerHandle()
{
	bEnableItemSlotTwo = true;
	OnEndCoolDownSlotTwo.Broadcast();
}

void UInventoryComponent::EndSlotThreeTimerHandle()
{
	bEnableItemSlotThree = true;
	OnEndCoolDownSlotThree.Broadcast();
}

void UInventoryComponent::EndSlotFourTimerHandle()
{
	bEnableItemSlotFour = true;
	OnEndCoolDownSlotFour.Broadcast();
}

void UInventoryComponent::EndSlotFiveTimerHandle()
{
	bEnableItemSlotFive = true;
	OnEndCoolDownSlotFive.Broadcast();
}

void UInventoryComponent::EndSlotSixTimerHandle()
{
	bEnableItemSlotSix = true;
	OnEndCoolDownSlotSix.Broadcast();
}

void UInventoryComponent::EffectConsumable(const FName& ItemCode)
{
	FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
	if (Spec)
	{
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

		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(GetOwner());
		if (DefaultCharacter)
		{
			DefaultCharacter->UpdateStatManager(Target, EStatUpdateType::ESUT_Plus, AbilityPoint);
		}
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

void UInventoryComponent::HandleItemSlotCoolDown()
{
	if (!bEnableItemSlotOne)
	{
		NotifyCoolDown(ItemSlotOneTimerHandle, OnProgressCoolDownSlotOne);
	}
	if (!bEnableItemSlotTwo)
	{
		NotifyCoolDown(ItemSlotTwoTimerHandle, OnProgressCoolDownSlotTwo);
	}
	if (!bEnableItemSlotThree)
	{
		NotifyCoolDown(ItemSlotThreeTimerHandle, OnProgressCoolDownSlotThree);
	}
	if (!bEnableItemSlotFour)
	{
		NotifyCoolDown(ItemSlotFourTimerHandle, OnProgressCoolDownSlotFour);
	}
	if (!bEnableItemSlotFive)
	{
		NotifyCoolDown(ItemSlotFiveTimerHandle, OnProgressCoolDownSlotFive);
	}
	if (!bEnableItemSlotSix)
	{
		NotifyCoolDown(ItemSlotSixTimerHandle, OnProgressCoolDownSlotSix);
	}
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

			OnEquipped.Broadcast(ItemCode, *Spec);
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

			if (ItemSpec->Type == EItemType::EIT_Consumable)
			{
				if (SlotOne.IsNone())
				{
					SlotOne = ItemCode;
				}
				else if (SlotTwo.IsNone())
				{
					SlotTwo = ItemCode;
				}
				else if (SlotThree.IsNone())
				{
					SlotThree = ItemCode;
				}
				else if (SlotFour.IsNone())
				{
					SlotFour = ItemCode;
				}
				else if (SlotFive.IsNone())
				{
					SlotFive = ItemCode;
				}
				else if (SlotSix.IsNone())
				{
					SlotSix = ItemCode;
				}
			}
		}
		OnAdded.Broadcast(ItemCode, *ItemSpec);
	}
}

void UInventoryComponent::UseItem(const FName& ItemCode)
{
	if (ItemCode.IsNone() || ItemSpecData == nullptr) return;

	FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
	if (Spec)
	{
		EItemType ItemType = Spec->Type;
		if (ItemType == EItemType::EIT_Consumable)
		{
			if (ItemList.Contains(ItemCode))
			{
				const FName CopyItemCode = ItemCode;
				// 데이터 업데이트
				if (ItemList[ItemCode] == 1)
				{
					ItemList.Remove(ItemCode);
					RemoveItemSlot(ItemCode);
				}
				else
				{
					ItemList[ItemCode]--;
				}

				OnUsed.Broadcast(CopyItemCode, *Spec);

				// 실제 데이터 적용
				EffectConsumable(CopyItemCode);

				SpawnConsumeParticle(Spec->EffectParticle);

				PlayConsumeSound();
			}
		}
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

void UInventoryComponent::HandleSlotOne()
{
	if (bEnableItemSlotOne && ItemSpecData && SlotOne != FName())
	{
		bEnableItemSlotOne = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotOne, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotOneTimerHandle, this, &UInventoryComponent::EndSlotOneTimerHandle, CoolDown);

			UseItem(SlotOne);
		}
	}
}

void UInventoryComponent::HandleSlotTwo()
{
	if (bEnableItemSlotTwo && ItemSpecData && HasItemInContainer(EItemNumber::EIN_2))
	{
		bEnableItemSlotTwo = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotTwo, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotTwoTimerHandle, this, &UInventoryComponent::EndSlotTwoTimerHandle, CoolDown);

			UseItem(SlotTwo);
		}
	}
}

void UInventoryComponent::HandleSlotThree()
{
	if (bEnableItemSlotThree && ItemSpecData && HasItemInContainer(EItemNumber::EIN_3))
	{
		bEnableItemSlotThree = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotThree, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotThreeTimerHandle, this, &UInventoryComponent::EndSlotThreeTimerHandle, CoolDown);

			UseItem(SlotThree);
		}
	}
}

void UInventoryComponent::HandleSlotFour()
{
	if (bEnableItemSlotFour && ItemSpecData && HasItemInContainer(EItemNumber::EIN_4))
	{
		bEnableItemSlotFour = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotFour, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotFourTimerHandle, this, &UInventoryComponent::EndSlotFourTimerHandle, CoolDown);

			UseItem(SlotFour);
		}
	}
}

void UInventoryComponent::HandleSlotFive()
{
	if (bEnableItemSlotFive && ItemSpecData && HasItemInContainer(EItemNumber::EIN_5))
	{
		bEnableItemSlotFive = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotFive, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotFiveTimerHandle, this, &UInventoryComponent::EndSlotFiveTimerHandle, CoolDown);

			UseItem(SlotFive);
		}
	}
}

void UInventoryComponent::HandleSlotSix()
{
	if (bEnableItemSlotSix && ItemSpecData && HasItemInContainer(EItemNumber::EIN_6))
	{
		bEnableItemSlotSix = false;

		FItemSpec* ItemSpec = ItemSpecData->FindRow<FItemSpec>(SlotSix, "");
		if (ItemSpec)
		{
			const float& CoolDown = ItemSpec->Stats.CoolDown;

			GetWorld()->GetTimerManager().SetTimer(ItemSlotSixTimerHandle, this, &UInventoryComponent::EndSlotSixTimerHandle, CoolDown);

			UseItem(SlotSix);
		}
	}
}

const TArray<FName> UInventoryComponent::GetItemSlots() const
{
	const TArray<FName> SlotArray = { SlotOne, SlotTwo, SlotThree, SlotFour, SlotFive, SlotSix };
	return SlotArray;
}

void UInventoryComponent::RemoveItemSlot(const FName& ItemCode)
{
	if (SlotOne == ItemCode)
	{
		SlotOne = FName();
	}
	else if (SlotTwo == ItemCode)
	{
		SlotTwo = FName();
	}
	else if (SlotThree == ItemCode)
	{
		SlotThree = FName();
	}
	else if (SlotFour == ItemCode)
	{
		SlotFour = FName();
	}
	else if (SlotFive == ItemCode)
	{
		SlotFive = FName();
	}
	else if (SlotSix == ItemCode)
	{
		SlotSix = FName();
	}
}

void UInventoryComponent::SetItemSlotMapping(const FName& ItemCode, uint8 Idx)
{
	switch (Idx)
	{
	case 0:
		SlotOne = ItemCode;
		break;
	case 1:
		SlotTwo = ItemCode;
		break;
	case 2:
		SlotThree = ItemCode;
		break;
	case 3:
		SlotFour = ItemCode;
		break;
	case 4:
		SlotFive = ItemCode;
		break;
	case 5:
		SlotSix = ItemCode;
		break;
	}
}

FTimerHandle* UInventoryComponent::GetItemTimerHandle(EItemNumber ItemNum)
{
	FTimerHandle* TimerHandle = nullptr;

	switch (ItemNum)
	{
	case EItemNumber::EIN_1:
		TimerHandle = &ItemSlotOneTimerHandle;
		break;
	case EItemNumber::EIN_2:
		TimerHandle = &ItemSlotTwoTimerHandle;
		break;
	case EItemNumber::EIN_3:
		TimerHandle = &ItemSlotThreeTimerHandle;
		break;
	case EItemNumber::EIN_4:
		TimerHandle = &ItemSlotFourTimerHandle;
		break;
	case EItemNumber::EIN_5:
		TimerHandle = &ItemSlotFiveTimerHandle;
		break;
	case EItemNumber::EIN_6:
		TimerHandle = &ItemSlotSixTimerHandle;
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
		EnableItem = bEnableItemSlotOne;
		break;
	case EItemNumber::EIN_2:
		EnableItem = bEnableItemSlotTwo;
		break;
	case EItemNumber::EIN_3:
		EnableItem = bEnableItemSlotThree;
		break;
	case EItemNumber::EIN_4:
		EnableItem = bEnableItemSlotFour;
		break;
	case EItemNumber::EIN_5:
		EnableItem = bEnableItemSlotFive;
		break;
	case EItemNumber::EIN_6:
		EnableItem = bEnableItemSlotSix;
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
		TargetItem = SlotOne;
		break;
	case EItemNumber::EIN_2:
		TargetItem = SlotTwo;
		break;
	case EItemNumber::EIN_3:
		TargetItem = SlotThree;
		break;
	case EItemNumber::EIN_4:
		TargetItem = SlotFour;
		break;
	case EItemNumber::EIN_5:
		TargetItem = SlotFive;
		break;
	case EItemNumber::EIN_6:
		TargetItem = SlotSix;
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

