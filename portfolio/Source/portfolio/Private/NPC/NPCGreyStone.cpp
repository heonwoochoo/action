// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCGreyStone.h"

ANPCGreyStone::ANPCGreyStone()
{
	// 퀘스트 소유
	QuestList.Add(EQuestCode::EQC_0001);
}

void ANPCGreyStone::BeginPlay()
{
	Super::BeginPlay();
}
