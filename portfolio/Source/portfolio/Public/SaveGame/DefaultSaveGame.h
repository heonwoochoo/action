// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

/**
 * 게임 시작시 무조건 로드되는 파일
 * 세이브한 유저의 이름을 저장하고 있어 해당 이름의 슬롯을 불러옴
 */
UCLASS()
class PORTFOLIO_API UDefaultSaveGame : public USaveGame
{
	GENERATED_BODY()

private:
	// 해당 클래스의 슬롯 이름
	FString SlotName = "Default";

	// 저장된 유저의 고유한 이름
	TArray<FString> UserNames;

public:
	FString GetSlotName() const;

	void AddUser(FString UserName);
	
	void RemoveUser(FString UserName);

	TArray<FString> GetAllUserName() const;
};
