// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NPC/QuestSelectBoxList.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UQuestSelectBoxList::NativeConstruct()
{
	InitListButton();

	if (ArrowImage)
	{
		ArrowImage->SetBrushFromTexture(nullptr);
	}
}

void UQuestSelectBoxList::OnHoveredListButton()
{
	if (ArrowImage && DeactivatedArrowRight && !bIsSelected)
	{
		ArrowImage->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UQuestSelectBoxList::OnUnhoveredListButton()
{
	if (ArrowImage && !bIsSelected)
	{
		ArrowImage->SetBrushFromTexture(nullptr);
	}
}

void UQuestSelectBoxList::OnClickedListButton()
{
	if (!bIsSelected)
	{
		// 선택 활성화
		bIsSelected = true;
		if (ArrowImage && ActivatedArrowRight)
		{
			ArrowImage->SetBrushFromTexture(ActivatedArrowRight);
		}
	}
	else
	{
		// 비활성화
		bIsSelected = false;
		if (ArrowImage && DeactivatedArrowRight)
		{
			ArrowImage->SetBrushFromTexture(DeactivatedArrowRight);
		}
	}
}

void UQuestSelectBoxList::SetHeadlineText(const FText& InTitle)
{
	if (HeadlineText)
	{
		HeadlineText->SetText(InTitle);
	}
}

void UQuestSelectBoxList::SetStateText(const EQuestState& InState)
{
	check(StateText);

	FText NewStateText{};
	FColor NewColor{};

	switch (InState)
	{
	case EQuestState::EQS_Unserved:
		NewStateText = FText::FromString(TEXT("진행 가능"));
		NewColor = FColor::Cyan;
		break;
	case EQuestState::EQS_Progress:
		NewStateText = FText::FromString(TEXT("진행 중"));
		NewColor = FColor::Silver;
		break;
	case EQuestState::EQS_Complete:
		NewStateText = FText::FromString(TEXT("완료"));
		NewColor = FColor::Yellow;
		break;
	default:
		NewStateText = FText::FromString(TEXT("None"));
		NewColor = FColor::White;
	}

	StateText->SetText(NewStateText);
	StateText->SetColorAndOpacity(NewColor);
}

void UQuestSelectBoxList::InitListButton()
{
	if (ListButton)
	{
		ListButton->OnHovered.AddDynamic(this, &UQuestSelectBoxList::OnHoveredListButton);
		ListButton->OnUnhovered.AddDynamic(this, &UQuestSelectBoxList::OnUnhoveredListButton);
		ListButton->OnClicked.AddDynamic(this, &UQuestSelectBoxList::OnClickedListButton);
	}
}