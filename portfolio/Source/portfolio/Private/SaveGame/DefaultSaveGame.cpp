// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/DefaultSaveGame.h"

FString UDefaultSaveGame::GetSlotName() const
{
	return SlotName;
}

void UDefaultSaveGame::AddUser(FString UserName)
{
	UserNames.Add(UserName);
}

void UDefaultSaveGame::RemoveUser(FString UserName)
{
	UserNames.Remove(UserName);
}

TArray<FString> UDefaultSaveGame::GetAllUserName() const
{
	return UserNames;
}
