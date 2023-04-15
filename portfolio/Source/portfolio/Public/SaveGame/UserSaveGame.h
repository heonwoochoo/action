// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UUserSaveGame : public USaveGame
{
	GENERATED_BODY()
	
private:
	// 생성시 유저 이름과 일치
	FString SlotName;

	// 생성 날짜
	FDateTime CreatedDate;

	// 마지막 플레이 날짜
	FDateTime RecentDate;

public:
	FString GetSlotName() const;
	void SetSlotName(FString Name);

	FDateTime GetCreatedDate() const;
	void SetCreatedDate(FDateTime Date);

	FDateTime GetRecentDate() const;
	void SetRecentDate(FDateTime Date);
};
