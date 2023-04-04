// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/InfoContainer.h"
#include "Components/TextBlock.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "CharacterTypes.h"
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
	ADText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetAttackDamage())));
}

void UInfoContainer::UpdateADDefenseText()
{
	ADDefenseText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetAttackDamageDefense())));
}

void UInfoContainer::UpdateAttackSpeedText()
{
	AttackSpeedText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetAttackSpeed())));
}

void UInfoContainer::UpdateCriticalText()
{
	CriticalText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetCritical())));
}

void UInfoContainer::UpdateAPText()
{
	APText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetAbilityPower())));
}

void UInfoContainer::UpdateAPDefenseText()
{
	APDefenseText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetAbilityPower())));
}

void UInfoContainer::UpdateCoolDownText()
{
	CoolDownText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetCoolDown())));
}

void UInfoContainer::UpdateMovementSpeedText()
{
	MovementSpeedText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetMovementSpeed())));
}

void UInfoContainer::UpdateHP()
{


	HpCurrent->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetHP())));
	HpMax->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetHPMax())));
	HPProgressBar->SetPercent(Character->GetCharacterStats().HP / Character->GetCharacterStats().GetHPMax());	
}

void UInfoContainer::UpdateStamina()
{
	StaminaCurrent->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetStamina())));
	StaminaMax->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetStaminaMax())));
	StaminaProgressBar->SetPercent(Character->GetCharacterStats().Stamina / Character->GetCharacterStats().GetStaminaMax());
}

void UInfoContainer::UpdateExp()
{
	ExpProgressBar->SetPercent(Character->GetCharacterStats().GetExp() / Character->GetCharacterStats().GetExpMax());
}

void UInfoContainer::UpdateLevel()
{
	LevelText->SetText(FText::FromString(FString::FromInt(Character->GetCharacterStats().GetLevel())));
}

void UInfoContainer::UpdateGold()
{
	GoldText->SetText(FText::FromString(FString::FromInt((int32)Character->GetCharacterStats().GetGold())));
}

void UInfoContainer::UpdateSkillOne()
{
	if (AbilityComponent && !AbilityComponent->GetCanSkillOne())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AbilityComponent->GetSkillOneHandle());
		if (RemainingTime != -1)
		{
			SkillOneCoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(RemainingTime)))));
			SkillOneCoolDownProgressBar->SetPercent(RemainingTime / AbilityComponent->GetSkillOne().CoolDown);
			
		}
	}
	else
	{
		SkillOneCoolDownText->SetText(FText::GetEmpty());
	}
}

void UInfoContainer::UpdateSkillOneImage()
{
	SkillOneImage->SetBrushFromTexture(AbilityComponent->GetSkillOne().Image);
}

void UInfoContainer::UpdateSkillTwo()
{
	if (AbilityComponent && !AbilityComponent->GetCanSkillTwo())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AbilityComponent->GetSkillTwoHandle());
		if (RemainingTime != -1)
		{
			SkillTwoCoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(RemainingTime)))));
			SkillTwoCoolDownProgressBar->SetPercent(RemainingTime / AbilityComponent->GetSkillTwo().CoolDown);
		}
	}
	else
	{
		SkillTwoCoolDownText->SetText(FText::GetEmpty());
	}
}

void UInfoContainer::UpdateSkillTwoImage()
{
	SkillTwoImage->SetBrushFromTexture(AbilityComponent->GetSkillTwo().Image);
}

void UInfoContainer::UpdateSkillThree()
{
	if (AbilityComponent && !AbilityComponent->GetCanSkillThree())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AbilityComponent->GetSkillThreeHandle());
		if (RemainingTime != -1)
		{
			SkillThreeCoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(RemainingTime)))));
			SkillThreeCoolDownProgressBar->SetPercent(RemainingTime / AbilityComponent->GetSkillThree().CoolDown);
		}
	}
	else
	{
		SkillThreeCoolDownText->SetText(FText::GetEmpty());
	}
}

void UInfoContainer::UpdateSkillThreeImage()
{
	SkillThreeImage->SetBrushFromTexture(AbilityComponent->GetSkillThree().Image);
}

void UInfoContainer::UpdateSkillFour()
{
	if (AbilityComponent && !AbilityComponent->GetCanSkillFour())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AbilityComponent->GetSkillFourHandle());
		if (RemainingTime != -1)
		{
			SkillFourCoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(RemainingTime)))));
			SkillFourCoolDownProgressBar->SetPercent(RemainingTime / AbilityComponent->GetSkillFour().CoolDown);
		}
	}
	else
	{
		SkillFourCoolDownText->SetText(FText::GetEmpty());
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
		UDataTable* PotionDataTable = InventoryComponent->GetPotionDataTable();
		if (PotionDataTable)
		{
			TArray<FPotionInfo*> OutPotionRowArrays;
			PotionDataTable->GetAllRows<FPotionInfo>("", OutPotionRowArrays);

			TMap<EItemName, uint8> Inventory = InventoryComponent->GetItemAmountMap();

			RemovePotionUI();
			for (auto Item : Inventory)
			{
				if (CheckPotion(Item.Key))
				{
					for (auto Row : OutPotionRowArrays)
					{
						if (Row->Name == Item.Key)
						{
							UpdatePotionUI(Row->Image, Item.Value);
						}
					}
				}
			}
		}
	}
}

void UInfoContainer::UpdatePotionUI(UTexture2D* Image, uint8 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdatePotionUI"));
	if (PotionIdx < 3)
	{
		ItemPotions[PotionIdx].Image->SetBrushFromTexture(Image);
		ItemPotions[PotionIdx].Image->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
		ItemPotions[PotionIdx].Amount->SetText(FText::FromString(FString::FromInt(Amount)));
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