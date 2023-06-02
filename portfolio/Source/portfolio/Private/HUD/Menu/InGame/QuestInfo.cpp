// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/QuestInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "Components/VerticalBox.h"
#include "HUD/Menu/InGame/QuestDetail.h"
#include "DefaultCharacter.h"
#include "Component/QuestClientComponent.h"
#include "HUD/Menu/InGame/QuestHeadline.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UQuestInfo::NativeConstruct()
{
	Super::NativeConstruct();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CharacterController->OnChangedInputMode.AddDynamic(this, &UQuestInfo::OnChangedInputMode);
		
		// 플레이어로부터 퀘스트 정보 받아오기
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(CharacterController->GetCharacter());
		if (DefaultCharacter)
		{
			UQuestClientComponent* QuestClientComponent = DefaultCharacter->GetQuestClientComponent();
			if (QuestClientComponent)
			{
				QuestList = QuestClientComponent->GetQuestList();

				for (auto& QuestClientData : QuestList)
				{
					if (QuestHeadlineClass && QuestBox)
					{
						UQuestHeadline* Headline = Cast<UQuestHeadline>(CreateWidget(CharacterController, QuestHeadlineClass));
						if (Headline)
						{
							Headline->SetQuestInfo(this);
							Headline->SetQuestCode(QuestClientData.QuestCode);

							const FText& Title = QuestClientData.Quest.Title;
							Headline->SetHeadlineText(Title);

							QuestBox->AddChild(Headline);

							OnClicked.AddDynamic(Headline, &UQuestHeadline::OnClickedQuest);
						}
					}
				}
			}
		}
	}

	// 디테일 창은 퀘스트 클릭시에만 나타나게 해야함, 그러므로 처음엔 숨김처리
	if (QuestDetail)
	{
		QuestDetail->SetVisibility(ESlateVisibility::Hidden);
		OnClicked.AddDynamic(QuestDetail, &UQuestDetail::OnClickedQuest);
	}
}

void UQuestInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestInfo::NativeDestruct()
{
	Super::NativeDestruct();
}

void UQuestInfo::OnReleasedTitleDragButton()
{
	Super::OnReleasedTitleDragButton();

	// 위치저장
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& CurrentLocation = CanvasPanelSlot->GetPosition();
			CharacterController->SetQuestInitialLocation(CurrentLocation);
		}
	}
}

void UQuestInfo::InitCanvasLocation()
{
	Super::InitCanvasLocation();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController && InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& Location = CharacterController->GetQuestInitialLocation();
			CanvasPanelSlot->SetPosition(Location);
		}
	}
}

void UQuestInfo::OnChangedInputMode(const EInputMode& Mode)
{
	if (Mode == EInputMode::EIM_Game)
	{
		RemoveFromParent();
	}
}