// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/ProgressBarContainer.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UProgressBarContainer::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UProgressBarContainer::Init()
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		const FCharacterStats& Stats = DefaultCharacter->GetCharacterStats();

		UpdateHealth(Stats.HP, Stats.HPMax);
		UpdateStamina(Stats.Stamina, Stats.StaminaMax);
		UpdateExp(Stats.Exp, Stats.ExpMax);
		UpdateLevel(Stats.Level);

		DefaultCharacter->OnChangedHealth.AddDynamic(this, &UProgressBarContainer::UpdateHealth);
		DefaultCharacter->OnChangedStamina.AddDynamic(this, &UProgressBarContainer::UpdateStamina);
		DefaultCharacter->OnChangedExp.AddDynamic(this, &UProgressBarContainer::UpdateExp);
		DefaultCharacter->OnChangedLevel.AddDynamic(this, &UProgressBarContainer::UpdateLevel);
	}
}

void UProgressBarContainer::UpdateHealth(const float& CurrentHp, const float& MaxHp)
{
	HpCurrent->SetText(FText::FromString(FString::FromInt((int32)CurrentHp)));
	HpMax->SetText(FText::FromString(FString::FromInt((int32)MaxHp)));
	HPProgressBar->SetPercent(CurrentHp / MaxHp);
}

void UProgressBarContainer::UpdateStamina(const float& CurrentSp, const float& MaxSp)
{
	StaminaCurrent->SetText(FText::FromString(FString::FromInt((int32)CurrentSp)));
	StaminaMax->SetText(FText::FromString(FString::FromInt((int32)MaxSp)));
	StaminaProgressBar->SetPercent(CurrentSp / MaxSp);
}

void UProgressBarContainer::UpdateExp(const float& CurrentExp, const float& MaxExp)
{
	ExpProgressBar->SetPercent(CurrentExp / MaxExp);
}

void UProgressBarContainer::UpdateLevel(const int32& NewLevel)
{
	LevelText->SetText(FText::FromString(FString::FromInt(NewLevel)));
}