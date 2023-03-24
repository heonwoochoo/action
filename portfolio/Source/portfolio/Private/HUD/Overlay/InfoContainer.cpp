// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/InfoContainer.h"
#include "Components/TextBlock.h"
#include "portfolio/portfolioCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "CharacterTypes.h"
#include "Component/AbilityComponent.h"

void UInfoContainer::NativeConstruct()
{
	Super::NativeConstruct();
	 Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	 if (Character)
	 { 
		 AbilityComponent = Character->GetAbilityComponent();
		 if (AbilityComponent)
		 {
			 Init();
		 }
	 }
}

void UInfoContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	UpdateSkillOne();
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