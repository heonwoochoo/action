// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/UserSaveGame.h"

FString UUserSaveGame::GetSlotName() const
{
	return SlotName;
}

void UUserSaveGame::SetSlotName(FString Name)
{
	SlotName = Name;
}

FDateTime UUserSaveGame::GetCreatedDate() const
{
	return CreatedDate;
}

void UUserSaveGame::SetCreatedDate(FDateTime Date)
{
	CreatedDate = Date;
}

FDateTime UUserSaveGame::GetRecentDate() const
{
	return RecentDate;
}

void UUserSaveGame::SetRecentDate(FDateTime Date)
{
	RecentDate = Date;
}
