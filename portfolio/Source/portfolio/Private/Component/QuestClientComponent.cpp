// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/QuestClientComponent.h"

UQuestClientComponent::UQuestClientComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestClientComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UQuestClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UQuestClientComponent::AddQuest(const EQuestCode& InQuestCode, const FQuest& InQuest)
{
	// 기존에 수락한 퀘스트인지 중복을 검사
	for (auto& Data : QuestList)
	{
		if (Data.QuestCode == InQuestCode) return;
	}

	FQuestClientData NewData;
	NewData.QuestCode = InQuestCode;
	NewData.Quest = InQuest;
	NewData.QuestState = EQuestState::EQS_Progress;
	
	QuestList.Add(NewData);
}