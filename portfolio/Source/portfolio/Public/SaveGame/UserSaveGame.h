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
	
public:
	// 생성시 유저 이름과 일치
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;

	// 생성 날짜
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FDateTime CreatedDate;

	// 마지막 플레이 날짜
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FDateTime RecentDate;

};
