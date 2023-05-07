// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/QuestServerComponent.h"

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
		const FString& QuestCode = QuestCodeType->GetDisplayNameTextByValue((int64)InQuestCode).ToString();
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