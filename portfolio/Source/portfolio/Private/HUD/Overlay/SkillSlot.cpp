// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/SkillSlot.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Component/AbilityComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void USkillSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillSlot::Init()
{
	if (SkillNumber == ESkillNumber::ESN_None) return;

	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		UAbilityComponent* AbilityComponent = DefaultCharacter->GetAbilityComponent();
		if (AbilityComponent)
		{
			FCharacterSkill SelectedSkill{};
			FText Input{};

			switch (SkillNumber)
			{
			case ESkillNumber::ESN_One:
				SelectedSkill = AbilityComponent->GetSkillOne();
				Input = FText::FromString(TEXT("1"));
				break;
			case ESkillNumber::ESN_Two:
				SelectedSkill = AbilityComponent->GetSkillTwo();
				Input = FText::FromString(TEXT("2"));
				break;
			case ESkillNumber::ESN_Three:
				SelectedSkill = AbilityComponent->GetSkillThree();
				Input = FText::FromString(TEXT("3"));
				break;
			case ESkillNumber::ESN_Four:
				SelectedSkill = AbilityComponent->GetSkillFour();
				Input = FText::FromString(TEXT("4"));
				break;
			}

			if (Image && SlotBorder && InputKey)
			{
				Image->SetBrushFromTexture(SelectedSkill.Image);
				SlotBorder->SetBrushFromTexture(SlotReadyBorder);
				InputKey->SetText(Input);
			}
		}
	}
}

void USkillSlot::UpdateCoolDown(const float& Remaining, const float& Rate)
{
	if (Remaining != -1)
	{
		CoolDownText->SetText(FText::FromString(FString::FromInt((FMath::RoundToInt(Remaining)))));
		CoolDownProgressBar->SetPercent(Remaining / Rate);
	}
}

void USkillSlot::ResetCooldDown()
{
	CoolDownText->SetText(FText::GetEmpty());
	CoolDownProgressBar->SetPercent(0.f);
}
