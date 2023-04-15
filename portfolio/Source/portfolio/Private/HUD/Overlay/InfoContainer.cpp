﻿// Fill out your copyright notice in the Description page of Project Settings.


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

	UpdateItemCoolDown1();
	UpdateItemCoolDown2();
	UpdateItemCoolDown3();
	UpdateItemCoolDown4();
	UpdateItemCoolDown5();
	UpdateItemCoolDown6();
}

void UInfoContainer::Init()
{
	UpdateADText();
	UpdateADDefenseText();
	UpdateAttackSpeedText();
	UpdateCriticalText();
	UpdateAPText();
	UpdateAPDefenseText();
	UpdateCoolDownText();
	UpdateMovementSpeedText();
	UpdateHP();
	UpdateStamina();
	UpdateExp();
	UpdateLevel();
	UpdateGold();
	UpdateSkillOne();
	UpdateSkillOneImage();
	UpdateSkillTwo();
	UpdateSkillTwoImage();
	UpdateSkillThree();
	UpdateSkillThreeImage();
	UpdateSkillFour();
	UpdateSkillFourImage();

	RemovePotionUI();
}

void UInfoContainer::UpdateADText()
{
	ADText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().AttackDamage)));
}

void UInfoContainer::UpdateADDefenseText()
{
	ADDefenseText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().AttackDamageDefense)));
}

void UInfoContainer::UpdateAttackSpeedText()
{
	AttackSpeedText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().AttackSpeed)));
}

void UInfoContainer::UpdateCriticalText()
{
	CriticalText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().Critical)));
}

void UInfoContainer::UpdateAPText()
{
	APText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().AbilityPower)));
}

void UInfoContainer::UpdateAPDefenseText()
{
	APDefenseText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().AbilityPowerDefense)));
}

void UInfoContainer::UpdateCoolDownText()
{
	CoolDownText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().CoolDown)));
}

void UInfoContainer::UpdateMovementSpeedText()
{
	MovementSpeedText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().MovementSpeed)));
}

void UInfoContainer::UpdateHP()
{
	HpCurrent->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().HP)));
	HpMax->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().HPMax)));
	HPProgressBar->SetPercent(Character->GetCharacterStats().HP / Character->GetCharacterStats().HPMax);	
}

void UInfoContainer::UpdateStamina()
{
	StaminaCurrent->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().Stamina)));
	StaminaMax->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().StaminaMax)));
	StaminaProgressBar->SetPercent(Character->GetCharacterStats().Stamina / Character->GetCharacterStats().StaminaMax);
}

void UInfoContainer::UpdateExp()
{
	ExpProgressBar->SetPercent(Character->GetCharacterStats().Exp / Character->GetCharacterStats().ExpMax);
}

void UInfoContainer::UpdateLevel()
{
	LevelText->SetText(FText::FromString(FString::FromInt(Character->GetCharacterStats().Level)));
}

void UInfoContainer::UpdateGold()
{
	GoldText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().Gold)));
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

void UInfoContainer::UpdatePotionInventory()
{
	if (InventoryComponent)
	{
		RemovePotionUI();
			
		// 키보드 매핑 초기화
		InventoryComponent->ResetItemPotionMapping();

		CheckItemPotionInInventory();
	}
}

void UInfoContainer::UpdatePotionAmount(EItemName Name, UTexture2D* Image, uint8 Amount)
{
	if (PotionIdx < 3)
	{
		ItemPotions[PotionIdx].Image->SetBrushFromTexture(Image);
		ItemPotions[PotionIdx].Image->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
		ItemPotions[PotionIdx].Amount->SetText(FText::FromString(FString::FromInt(Amount)));

		// 키보드 매핑 재등록
		InventoryComponent->SetItemPotionMapping(Name, PotionIdx);

		// 다음 칸의 UI를 업데이트 하기 위해 인덱스 증가
		PotionIdx++;
	}
}

void UInfoContainer::RemovePotionUI()
{
	PotionIdx = 0;
	for (auto Potion : ItemPotions)
	{
		Potion.Amount->SetText(FText());
		Potion.Image->SetBrushFromTexture(nullptr);
		Potion.Image->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f));
	}
}

bool UInfoContainer::CheckPotion(EItemName Name)
{
	bool result =
		Name == EItemName::EIN_HealthPotion ||
		Name == EItemName::EIN_StaminaPotion;
	return result;
}

void UInfoContainer::InitItemPotions()
{
	ItemPotions.Add({ ItemImage1 ,Item1_Amount });
	ItemPotions.Add({ ItemImage2 ,Item2_Amount });
	ItemPotions.Add({ ItemImage3 ,Item3_Amount });
}

void UInfoContainer::CheckItemPotionInInventory()
{
	UDataTable* PotionDataTable = InventoryComponent->GetPotionDataTable();
	if (PotionDataTable)
	{
		TMap<EItemName, uint8> Inventory = InventoryComponent->GetItemAmountMap();
		for (auto Item : Inventory)
		{
			if (CheckPotion(Item.Key))
			{
				FName RowName;
				switch (Item.Key)
				{
				case EItemName::EIN_HealthPotion:
					RowName = "HealthPotion";
					break;
				case EItemName::EIN_StaminaPotion:
					RowName = "StaminaPotion";
					break;
				}
				FPotionInfo* PotionInfo = PotionDataTable->FindRow<FPotionInfo>(RowName, "");
				UpdatePotionAmount(PotionInfo->Name, PotionInfo->Image, Item.Value);
			}
		}
	}
}

void UInfoContainer::UpdateItemCoolDown1()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_1))
	{	
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_1);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_1);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText1, ItemCoolDownProgressBar1, IsEnable);
	}
}

void UInfoContainer::UpdateItemCoolDown2()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_2))
	{
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_2);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_2);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText2, ItemCoolDownProgressBar2, IsEnable);
	}
}

void UInfoContainer::UpdateItemCoolDown3()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_3))
	{
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_3);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_3);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText3, ItemCoolDownProgressBar3, IsEnable);
	}
}

void UInfoContainer::UpdateItemCoolDown4()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_4))
	{
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_4);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_4);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText4, ItemCoolDownProgressBar4, IsEnable);
	}
}

void UInfoContainer::UpdateItemCoolDown5()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_5))
	{
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_5);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_5);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText5, ItemCoolDownProgressBar5, IsEnable);
	}
}

void UInfoContainer::UpdateItemCoolDown6()
{
	if (InventoryComponent && InventoryComponent->HasItemInContainer(EItemNumber::EIN_6))
	{	
		FTimerHandle* TimerHandle = InventoryComponent->GetItemTimerHandle(EItemNumber::EIN_6);
		bool IsEnable = InventoryComponent->GetEnableItem(EItemNumber::EIN_6);
		UpdateCoolDownUI(TimerHandle, ItemCoolDownText6, ItemCoolDownProgressBar6, IsEnable);
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