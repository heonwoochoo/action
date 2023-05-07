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

	if (Text3DMarkClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;

		Text3DMark = GetWorld()->SpawnActor<AText3DMark>(Text3DMarkClass, SpawnParameters);
		if (Text3DMark)
		{
			// 테스트용
			Text3DMark->SetText(FText::FromString(TEXT("!")));
			Text3DMark->SetTextColor(ETextMaterialColor::ETMC_Yellow);
			Text3DMark->SetLocationOwnerHeadup();
		}
	}
}
