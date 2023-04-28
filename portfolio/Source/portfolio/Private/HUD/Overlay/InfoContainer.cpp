// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/InfoContainer.h"
#include "Components/TextBlock.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Types/CharacterTypes.h"
#include "Component/AbilityComponent.h"
#include "Components/Image.h"
#include "Component/InventoryComponent.h"
#include "Components/HorizontalBox.h"
#include "HUD/Overlay/SkillSlot.h"
#include "HUD/Overlay/ItemSlot.h"

void UInfoContainer::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{ 
		AbilityComponent = Character->GetAbilityComponent();

		InventoryComponent = Character->GetInventoryComponent();
	}

	InitSkillSlot();
	InitItemSlot();
}

void UInfoContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInfoContainer::InitSkillSlot()
{
	if (SkillSlotBox)
	{
		TArray<UWidget*> SkillSlots = SkillSlotBox->GetAllChildren();

		for (ESkillNumber Num : TEnumRange<ESkillNumber>())
		{
			USkillSlot* SkillSlot = Cast<USkillSlot>(SkillSlots[(uint8)Num]);
			if (SkillSlot)
			{
				SkillSlot->SetSkillNumber(Num);
				SkillSlot->Init();

				if (AbilityComponent)
				{
					if (SkillSlot == SkillOneSlot)
					{
						AbilityComponent->OnProgressSkillOne.AddDynamic(SkillSlot, &USkillSlot::UpdateCoolDown);
						AbilityComponent->OnEndSkillOne.AddDynamic(SkillSlot, &USkillSlot::ResetCooldDown);
					}
					else if (SkillSlot == SkillTwoSlot)
					{
						AbilityComponent->OnProgressSkillTwo.AddDynamic(SkillSlot, &USkillSlot::UpdateCoolDown);
						AbilityComponent->OnEndSkillTwo.AddDynamic(SkillSlot, &USkillSlot::ResetCooldDown);
					}
					else if (SkillSlot == SkillThreeSlot)
					{
						AbilityComponent->OnProgressSkillThree.AddDynamic(SkillSlot, &USkillSlot::UpdateCoolDown);
						AbilityComponent->OnEndSkillThree.AddDynamic(SkillSlot, &USkillSlot::ResetCooldDown);
					}
					else if (SkillSlot == SkillFourSlot)
					{
						AbilityComponent->OnProgressSkillFour.AddDynamic(SkillSlot, &USkillSlot::UpdateCoolDown);
						AbilityComponent->OnEndSkillFour.AddDynamic(SkillSlot, &USkillSlot::ResetCooldDown);
					}
				}
			}
		}
	}
}

void UInfoContainer::InitItemSlot()
{
	TArray<UWidget*> ItemSlots = ItemSlotBox->GetAllChildren();

	for (EItemNumber Num : TEnumRange<EItemNumber>())
	{
		UItemSlot* ItemSlot = Cast<UItemSlot>(ItemSlots[(uint8)Num]);
		if (ItemSlot)
		{
			ItemSlot->Reset();
			ItemSlot->SetSlotNumber(Num);
			ItemSlot->Init();

			if (InventoryComponent)
			{
				if (ItemSlot == ItemOneSlot)
				{
					InventoryComponent->OnProgressCoolDownSlotOne.AddDynamic(ItemSlot, &UItemSlot::UpdateCoolDownSlot);
					InventoryComponent->OnEndCoolDownSlotOne.AddDynamic(ItemSlot, &UItemSlot::ResetCoolDownSlot);
				}
				else if (ItemSlot == ItemTwoSlot)
				{
					InventoryComponent->OnProgressCoolDownSlotTwo.AddDynamic(ItemSlot, &UItemSlot::UpdateCoolDownSlot);
					InventoryComponent->OnEndCoolDownSlotTwo.AddDynamic(ItemSlot, &UItemSlot::ResetCoolDownSlot);
				}
				else if (ItemSlot == ItemThreeSlot)
				{
					InventoryComponent->OnProgressCoolDownSlotThree.AddDynamic(ItemSlot, &UItemSlot::UpdateCoolDownSlot);
					InventoryComponent->OnEndCoolDownSlotThree.AddDynamic(ItemSlot, &UItemSlot::ResetCoolDownSlot);
				}
				else if (ItemSlot == ItemFourSlot)
				{
					InventoryComponent->OnProgressCoolDownSlotFour.AddDynamic(ItemSlot, &UItemSlot::UpdateCoolDownSlot);
					InventoryComponent->OnEndCoolDownSlotFour.AddDynamic(ItemSlot, &UItemSlot::ResetCoolDownSlot);
				}

				InventoryComponent->OnUsed.AddDynamic(ItemSlot, &UItemSlot::OnUsedItem);
				InventoryComponent->OnAdded.AddDynamic(ItemSlot, &UItemSlot::OnAddedItem);
			}
		}
	}
}