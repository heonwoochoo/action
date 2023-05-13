// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/QuestDetail.h"
#include "DefaultCharacter.h"
#include "Component/QuestClientComponent.h"
#include "Controller/CharacterController.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Component/InventoryComponent.h"
#include "Types/ItemTypes.h"
#include "Components/Image.h"
#include "HelperFunction.h"

void UQuestDetail::NativeConstruct()
{
	Super::NativeConstruct();

}

void UQuestDetail::OnClickedQuest(const EQuestCode& InCode)
{
	SetVisibility(ESlateVisibility::Visible);

	// 플레이어로부터 퀘스트 정보 받아오기
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(PlayerController->GetCharacter());
		if (DefaultCharacter)
		{
			UQuestClientComponent* QuestClientComponent = DefaultCharacter->GetQuestClientComponent();
			if (QuestClientComponent)
			{
				const TArray<FQuestClientData>& QuestList = QuestClientComponent->GetQuestList();
				for (auto& QuetClientData : QuestList)
				{
					if (QuetClientData.QuestCode == InCode)
					{
						// 현재 퀘스트의 정보를 얻어옴
						const FQuest& Quest = QuetClientData.Quest;

						// 요약 텍스트
						if (SummaryText)
						{
							SummaryText->SetText(Quest.Summary);
						}

						// 조건 텍스트
						if (ConditionText)
						{
							if (Quest.EnemyConditions.Num() > 0)
							{
								for (auto& Condition : Quest.EnemyConditions)
								{
									const FName& EnemyCode = Condition.EnemyCode;
									const int32& CurrentKillCount = Condition.CurrentKillCount;
									const int32& MaxKillCount = Condition.MaxKillCount;

									// ex) Man: 1/60
									const FString& FormatString = 
										UHelperFunction::GetNameFromEnemyCode(EnemyCode).ToString() + FString(TEXT(": ")) +
										FString::FromInt(CurrentKillCount) + FString(TEXT("/")) +
										FString::FromInt(MaxKillCount);

									ConditionText->SetText(FText::FromString(FormatString));
								}
							}
						}

						// 보상 텍스트, 이미지
						const int32& Exp = Quest.QuestReward.Exp;
						const int32& Gold = Quest.QuestReward.Gold;
						const TMap<FName, int32>& ItemMap = Quest.QuestReward.ItemMap;

						if (Exp > 0 && ExpText)
						{
							if (ExpBox)
							{
								ExpBox->SetVisibility(ESlateVisibility::Visible);
							}

							ExpText->SetText(FText::FromString(FString::FromInt(Exp)));
						}
						else
						{
							if (ExpBox)
							{
								ExpBox->SetVisibility(ESlateVisibility::Hidden);
							}
						}

						if (Gold > 0 && GoldText)
						{
							if (GoldBox)
							{
								GoldBox->SetVisibility(ESlateVisibility::Visible);
							}

							GoldText->SetText(FText::FromString(FString::FromInt(Gold)));
						}
						else
						{
							if (GoldBox)
							{
								GoldBox->SetVisibility(ESlateVisibility::Hidden);
							}
						}

						if (ItemMap.Num() > 0)
						{
							if (ItemBox)
							{
								ItemBox->SetVisibility(ESlateVisibility::Visible);
							}

							for (auto& Item : ItemMap)
							{
								UInventoryComponent* InventoryComponent = DefaultCharacter->GetInventoryComponent();
								if (InventoryComponent)
								{
									UDataTable* DataTable = InventoryComponent->GetItemDataTable();
									if (DataTable)
									{
										FItemSpec* Spec = DataTable->FindRow<FItemSpec>(Item.Key, "");
										if (Spec)
										{
											if (ItemImage && ItemText)
											{
												ItemImage->SetBrushFromTexture(Spec->Image);
												ItemText->SetText(FText::FromName(Spec->Name));
											}
										}
									}
								}
							}
						}
						else
						{
							if (ItemBox)
							{
								ItemBox->SetVisibility(ESlateVisibility::Hidden);
							}
						}
					}
				}
			}
		}
	}
}