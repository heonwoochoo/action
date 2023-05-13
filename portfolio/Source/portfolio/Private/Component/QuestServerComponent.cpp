// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/QuestServerComponent.h"
#include "NPC/NPCGreyStone.h"
#include "DefaultCharacter.h"
#include "Component/QuestClientComponent.h"

UQuestServerComponent::UQuestServerComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestServerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UQuestServerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UQuestServerComponent::AddQuest(const EQuestCode& InQuestCode)
{
	if (!QuestList.Contains(InQuestCode))
	{
		QuestList.Add(InQuestCode);
		QuestList[InQuestCode] = EQuestState::EQS_Unserved;
	}
}

FQuest* UQuestServerComponent::GetQuestData(const EQuestCode& InQuestCode)
{
	const UEnum* QuestCodeType = FindObject<UEnum>(nullptr, TEXT("/Script/portfolio.EQuestCode"));
	if (QuestCodeType)
	{
		const FText& Text = QuestCodeType->GetDisplayNameTextByValue((int64)InQuestCode);
		const FString& QuestCode = Text.ToString();
		if (QuestData)
		{
			FQuest* Quest = QuestData->FindRow<FQuest>(FName(QuestCode), "");
			if (Quest)
			{
				return Quest;
			}
		}
	}

	return nullptr;
}

void UQuestServerComponent::SetQuestStateInList(const EQuestCode& TargetQuest, const EQuestState& InState)
{
	if (QuestList.Contains(TargetQuest))
	{
		QuestList[TargetQuest] = InState;
	}
}

void UQuestServerComponent::ServeQuestToPlayer(const EQuestCode& QuestCode)
{
	ANPCGreyStone* NPC = Cast<ANPCGreyStone>(GetOwner());
	if (NPC)
	{
		ADefaultCharacter* PlayerCharacter = NPC->GetNearPlayer();
		if (PlayerCharacter)
		{
			// 플레이어에게 퀘스트를 제공
			UQuestClientComponent* QuestClientComponent = PlayerCharacter->GetQuestClientComponent();
			if (QuestClientComponent)
			{
				const FQuest& Quest = *GetQuestData(QuestCode);
				QuestClientComponent->AddQuest(QuestCode, Quest);

				// 클라이언트의 퀘스트 상태변경에 관한 알림을 구독
				QuestClientComponent->OnChangedState.AddDynamic(this, &UQuestServerComponent::OnChangedClientQuestState);
			}

			// NPC의 퀘스트 상태 변경
			SetQuestStateInList(QuestCode, EQuestState::EQS_Progress);
		}
	}
}

void UQuestServerComponent::OnChangedClientQuestState(const EQuestCode& InQuestCode, const EQuestState& NewState)
{
	if (QuestList.Contains(InQuestCode))
	{
		const EQuestState& ServerQuestState = QuestList[InQuestCode];
	
		// 퀘스트가 완료되었음을 통보받으면 서버의 퀘스트 상태도 변경
		if (ServerQuestState == EQuestState::EQS_Progress && NewState == EQuestState::EQS_Complete)
		{
			QuestList[InQuestCode] = EQuestState::EQS_Complete;
		}
	}
}