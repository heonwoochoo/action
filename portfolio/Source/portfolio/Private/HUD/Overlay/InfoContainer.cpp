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

void UInfoContainer::NativeConstruct()
{
	Super::NativeConstruct();
	 Character = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	 if (Character)
	 { 
		 AbilityComponent = Character->GetAbilityComponent();
		 if (AbilityComponent)
		 {
			 Init();
		 }

		 InventoryComponent = Character->GetInventoryComponent();
	 }

	 InitItemPotions();
}

void UInfoContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	UpdateSkillOne();
	UpdateSkillTwo();
	UpdateSkillThree();
	UpdateSkillFour();
}

void UInfoContainer::Init()
{
	const FCharacterStats& Stats = Character->GetCharacterStats();

	UpdateHealth(Stats.HP, Stats.HPMax);
	UpdateStamina(Stats.Stamina, Stats.StaminaMax);
	UpdateExp(Stats.Exp, Stats.ExpMax);
	UpdateLevel(Stats.Level);

	UpdateSkillOne();
	UpdateSkillOneImage();
	UpdateSkillTwo();
	UpdateSkillTwoImage();
	UpdateSkillThree();
	UpdateSkillThreeImage();
	UpdateSkillFour();
	UpdateSkillFourImage();

	RemoveConsumableUI();
}

void UInfoContainer::UpdateSkillOne()
{
	if (AbilityComponent)
	{
		FTimerHandle* TimerHandle = AbilityComponent->GetSkillOneHandle();
		bool IsEnable = AbilityComponent->GetCanSkillOne();
		UpdateCoolDownUI(TimerHandle, SkillOneCoolDownText, SkillOneCoolDownProgressBar, IsEnable);
	}
}

void UInfoContainer::UpdateSkillOneImage()
{
	SkillOneImage->SetBrushFromTexture(AbilityComponent->GetSkillOne().Image);
}

void UInfoContainer::UpdateSkillTwo()
{
	if (AbilityComponent)
	{
		FTimerHandle* TimerHandle = AbilityComponent->GetSkillTwoHandle();
		bool IsEnable = AbilityComponent->GetCanSkillTwo();
		UpdateCoolDownUI(TimerHandle, SkillTwoCoolDownText, SkillTwoCoolDownProgressBar, IsEnable);
	}
}

void UInfoContainer::UpdateSkillTwoImage()
{
	SkillTwoImage->SetBrushFromTexture(AbilityComponent->GetSkillTwo().Image);
}

void UInfoContainer::UpdateSkillThree()
{
	if (AbilityComponent)
	{
		FTimerHandle* TimerHandle = AbilityComponent->GetSkillThreeHandle();
		bool IsEnable = AbilityComponent->GetCanSkillThree();
		UpdateCoolDownUI(TimerHandle, SkillThreeCoolDownText, SkillThreeCoolDownProgressBar, IsEnable);
	}
}

void UInfoContainer::UpdateSkillThreeImage()
{
	SkillThreeImage->SetBrushFromTexture(AbilityComponent->GetSkillThree().Image);
}

void UInfoContainer::UpdateHealth(const float& CurrentHp, const float& MaxHp)
{
	HpCurrent->SetText(FText::FromString(FString::FromInt((int32)CurrentHp)));
	HpMax->SetText(FText::FromString(FString::FromInt((int32)MaxHp)));
	HPProgressBar->SetPercent(Character->GetCharacterStats().HP / Character->GetCharacterStats().HPMax);
}

void UInfoContainer::UpdateStamina(const float& CurrentSp, const float& MaxSp)
{
	StaminaCurrent->SetText(FText::FromString(FString::FromInt((int32)CurrentSp)));
	StaminaMax->SetText(FText::FromString(FString::FromInt((int32)MaxSp)));
	StaminaProgressBar->SetPercent(Character->GetCharacterStats().Stamina / Character->GetCharacterStats().StaminaMax);
}

void UInfoContainer::UpdateExp(const float& CurrentExp, const float& MaxExp)
{
	ExpProgressBar->SetPercent(CurrentExp / MaxExp);
}

void UInfoContainer::UpdateLevel(const int32& NewLevel)
{
	LevelText->SetText(FText::FromString(FString::FromInt(NewLevel)));
}

void UInfoContainer::UpdateSkillFour()
{
	if (AbilityComponent)
	{
		FTimerHandle* TimerHandle = AbilityComponent->GetSkillFourHandle();
		bool IsEnable = AbilityComponent->GetCanSkillFour();
		UpdateCoolDownUI(TimerHandle, SkillFourCoolDownText, SkillFourCoolDownProgressBar, IsEnable);
	}
}

void UInfoContainer::UpdateSkillFourImage()
{
	SkillFourImage->SetBrushFromTexture(AbilityComponent->GetSkillFour().Image);
}

void UInfoContainer::UpdateConsumableQuickSlot()
{
	if (InventoryComponent)
	{
		RemoveConsumableUI();

		CheckItemPotionInInventory();
	}
}

void UInfoContainer::OnChangedQuickSlot(const FName& ItemCode, const FItemSpec& Spec)
{
	UpdateConsumableQuickSlot();
}

void UInfoContainer::UpdateConsumableAmount(const FName& ItemCode, UTexture2D* Image, uint8 Amount)
{
	if (PotionIdx < 3)
	{
		ItemPotions[PotionIdx].Image->SetBrushFromTexture(Image);
		ItemPotions[PotionIdx].Image->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
		ItemPotions[PotionIdx].Amount->SetText(FText::FromString(FString::FromInt(Amount)));

		// 키보드 매핑 재등록
		InventoryComponent->SetItemConsumableMapping(ItemCode, PotionIdx);

		// 다음 칸의 UI를 업데이트 하기 위해 인덱스 증가
		PotionIdx++;
	}
}

void UInfoContainer::RemoveConsumableUI()
{
	PotionIdx = 0;
	for (auto Potion : ItemPotions)
	{
		Potion.Amount->SetText(FText());
		Potion.Image->SetBrushFromTexture(nullptr);
		Potion.Image->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f));
	}
}

void UInfoContainer::InitItemPotions()
{
	ItemPotions.Add({ ItemImageOne ,ItemSlotOne_Amount });
	ItemPotions.Add({ ItemImageTwo ,ItemSlotTwo_Amount });
	ItemPotions.Add({ ItemImageThree ,ItemSlotThree_Amount });
}

void UInfoContainer::UpdateCoolDownSlotOne(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextOne->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarOne->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotOne()
{
	ItemCoolDownTextOne->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarOne->SetPercent(0.f);
}

void UInfoContainer::UpdateCoolDownSlotTwo(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextTwo->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarTwo->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotTwo()
{
	ItemCoolDownTextTwo->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarTwo->SetPercent(0.f);
}

void UInfoContainer::UpdateCoolDownSlotThree(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextThree->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarThree->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotThree()
{
	ItemCoolDownTextThree->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarThree->SetPercent(0.f);
}

void UInfoContainer::UpdateCoolDownSlotFour(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextFour->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarFour->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotFour()
{
	ItemCoolDownTextFour->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarFour->SetPercent(0.f);
}

void UInfoContainer::UpdateCoolDownSlotFive(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextFive->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarFive->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotFive()
{
	ItemCoolDownTextFive->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarFive->SetPercent(0.f);
}

void UInfoContainer::UpdateCoolDownSlotSix(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		ItemCoolDownTextSix->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		ItemCoolDownProgressBarSix->SetPercent(Remaining / Rate);
	}
}

void UInfoContainer::ResetCoolDownSlotSix()
{
	ItemCoolDownTextSix->SetText(FText::GetEmpty());
	ItemCoolDownProgressBarSix->SetPercent(0.f);
}

void UInfoContainer::CheckItemPotionInInventory()
{
	UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
	if (ItemSpecData)
	{
		const TMap<FName, uint8>& ItemList = InventoryComponent->GetItemList();
		for (const auto& Item : ItemList)
		{
			const FName& ItemCode = Item.Key;
			const uint8 Amount = Item.Value;

			FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
			if (Spec->Type == EItemType::EIT_Consumable)
			{
				UpdateConsumableAmount(ItemCode, Spec->Image, Amount);
			}
		}
	}
}

void UInfoContainer::UpdateCoolDownUI(FTimerHandle* TimerHandle, UTextBlock* Text, UProgressBar* ProgressBar, bool IsEnable)
{
	if (!IsEnable)
	{
		const float TimerRate = GetWorld()->GetTimerManager().GetTimerRate(*TimerHandle);
		const float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(*TimerHandle);
		if (RemainingTime != -1)
		{
			Text->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(RemainingTime)))));
			ProgressBar->SetPercent(RemainingTime / TimerRate);
		}
	}
	else
	{
		Text->SetText(FText::GetEmpty());
	}
}