// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserSaveGame.generated.h"


USTRUCT(BlueprintType)
struct FUserSavedSystemInfo
{
	GENERATED_USTRUCT_BODY()

	// 생성 날짜
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime CreatedDate;

	// 마지막 플레이 날짜
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime RecentDate;

	// 총 플레이 시간
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PlayTime;
};

USTRUCT(BlueprintType)
struct FUserInGameInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform Transform;
};

UCLASS()
class PORTFOLIO_API UUserSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// 생성시 유저 이름과 일치
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;

	// 시스템 정보 (날짜, 시간)
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FUserSavedSystemInfo SystemInfo;

	// 인게임 정보 (위치, 스탯)
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FUserInGameInfo InGameInfo;
};
