// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/QuestHeadline.h"
#include "Components/TextBlock.h"
#include "HUD/Menu/InGame/QuestInfo.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameMode/DefaultGameMode.h"
#include "Kismet/GameplayStatics.h"

void UQuestHeadline::NativeConstruct()
{
	Super::NativeConstruct();

	if (HeadlineText)
	{
		HeadlineText->SetColorAndOpacity(FColor::Silver);
	}

	if (HeadlineImage && DeactivatedImage)
	{
		HeadlineImage->SetBrushFromTexture(DeactivatedImage);
	}

	InitHeadlineButton();
}

void UQuestHeadline::OnHoveredHeadlineButton()
{
	if (HeadlineText)
	{
		HeadlineText->SetColorAndOpacity(FColor::White);
	}
}

void UQuestHeadline::OnUnhoveredHeadlineButton()
{
	if (QuestInfo)
	{
		const EQuestCode& SelectedQuest = QuestInfo->GetSelectedQuest();
		if (SelectedQuest != QuestCode)
		{
			if (HeadlineText)
			{
				HeadlineText->SetColorAndOpacity(FColor::Silver);
			}
		}
	}
}

void UQuestHeadline::OnClickedHeadlineButton()
{
	if (QuestInfo && QuestCode != EQuestCode::EQC_None)
	{
		QuestInfo->SetSelectedQuest(QuestCode);
		QuestInfo->OnClicked.Broadcast(QuestCode);
	}

	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UQuestHeadline::InitHeadlineButton()
{
	if (HeadlineButton)
	{
		HeadlineButton->OnHovered.AddDynamic(this, &UQuestHeadline::OnHoveredHeadlineButton);
		HeadlineButton->OnUnhovered.AddDynamic(this, &UQuestHeadline::OnUnhoveredHeadlineButton);
		HeadlineButton->OnClicked.AddDynamic(this, &UQuestHeadline::OnClickedHeadlineButton);
	}
}

void UQuestHeadline::SetHeadlineText(const FText& InText)
{
	if (HeadlineText)
	{
		HeadlineText->SetText(InText);
	}
}

void UQuestHeadline::OnClickedQuest(const EQuestCode& InCode)
{
	if (InCode == QuestCode)
	{
		if (ActivatedImage && HeadlineImage)
		{
			HeadlineImage->SetBrushFromTexture(ActivatedImage);
		}
	}
	else
	{
		if (DeactivatedImage && HeadlineImage)
		{
			HeadlineImage->SetBrushFromTexture(DeactivatedImage);
		}
	}
}