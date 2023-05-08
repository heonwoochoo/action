// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCGreyStone.h"
#include "NPC/Text3DMark.h"
#include "Component/QuestServerComponent.h"

ANPCGreyStone::ANPCGreyStone()
{
	// 퀘스트 등록
	QuestServerComponent = CreateDefaultSubobject<UQuestServerComponent>(TEXT("QuestServerComponent"));
	QuestServerComponent->AddQuest(EQuestCode::EQC_0001);
}

void ANPCGreyStone::BeginPlay()
{
	Super::BeginPlay();

	if (Text3DMarkClass && QuestServerComponent)
	{
		// 미진행 퀘스트가 있는지 확인
		// 하나라도 있으면 NPC 머리위에 ? 가 나타남
		const TMap<EQuestCode, EQuestState>& QuestList = QuestServerComponent->GetQuestList();
		for (auto& Quest : QuestList)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			Text3DMark = GetWorld()->SpawnActor<AText3DMark>(Text3DMarkClass, SpawnParameters);
			if (Text3DMark)
			{
				Text3DMark->SetLocationOwnerHeadup();
			}
		}
	}
}

void ANPCGreyStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Text3DMark)
	{
		Text3DMark->Update();
	}
}