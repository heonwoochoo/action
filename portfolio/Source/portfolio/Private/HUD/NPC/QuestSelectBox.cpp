// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NPC/QuestSelectBox.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Component/QuestServerComponent.h"
#include "HUD/NPC/QuestSelectBoxList.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UQuestSelectBox::NativeConstruct()
{
}

void UQuestSelectBox::Init(UQuestServerComponent* QuestServerComponent)
{
	if (QuestServerComponent)
	{
		const TMap<EQuestCode, EQuestState>& QuestList = QuestServerComponent->GetQuestList();
		for (auto& QuestElement : QuestList)
		{
			// 리스트 위젯 생성
			UQuestSelectBoxList* QuestBoxListWidget = Cast<UQuestSelectBoxList>(CreateWidget(this, QuestSelectBoxListClass));

			if (QuestBoxListWidget)
			{
				// 헤드라인으로 보여질 텍스트 설정
				const EQuestCode& QuestCode = QuestElement.Key;
				const FQuest* Quest = QuestServerComponent->GetQuestData(QuestCode);
				const FText& Title = Quest->Title;
				QuestBoxListWidget->SetHeadlineText(Title);

				// 상태 텍스트 설정
				const EQuestState& QuestState = QuestElement.Value;
				QuestBoxListWidget->SetStateText(QuestState);

				// 리스트 박스에 추가
				QuestListBox->AddChild(QuestBoxListWidget);
			}
		}
	}
}

void UQuestSelectBox::SetLocation(const FVector2D& InVector2D)
{
	if (InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			CanvasPanelSlot->SetPosition(InVector2D);
		}
	}
}