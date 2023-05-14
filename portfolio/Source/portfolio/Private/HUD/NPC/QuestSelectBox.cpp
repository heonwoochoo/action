// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NPC/QuestSelectBox.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Component/QuestServerComponent.h"
#include "HUD/NPC/QuestSelectBoxList.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "NPC/NPCGreyStone.h"

void UQuestSelectBox::NativeConstruct()
{
}

void UQuestSelectBox::NativeDestruct()
{
	if (QuestListBox)
	{
		TArray<UWidget*> AllChildWidget = QuestListBox->GetAllChildren();
		for (auto& Widget : AllChildWidget)
		{
			UQuestSelectBoxList* List = Cast<UQuestSelectBoxList>(Widget);

			if (Owner != nullptr)
			{
				ANPCGreyStone* GreyStone = Cast<ANPCGreyStone>(Owner);
				if (GreyStone)
				{
					UE_LOG(LogTemp, Warning, TEXT("Remove delegate at QuestSelectBox widget"));
					List->OnSelected.RemoveDynamic(GreyStone, &ANPCGreyStone::OnSelectedQuest);
				}
			}
		}
	}
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

				// 고유 코드 설정
				QuestBoxListWidget->SetQuestCode(QuestCode);

				// 리스트 선택시 NPC에게 알림이 가게 구독
				if (Owner != nullptr)
				{
					ANPCGreyStone* GreyStone = Cast<ANPCGreyStone>(Owner);
					if (GreyStone)
					{
						QuestBoxListWidget->OnSelected.AddDynamic(GreyStone, &ANPCGreyStone::OnSelectedQuest);
					}
				}

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