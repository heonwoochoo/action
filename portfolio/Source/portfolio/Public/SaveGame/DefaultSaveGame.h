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

public:
	// 저장된 유저의 고유한 이름
	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FString> UserNames;

};
