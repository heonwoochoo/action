// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestTypes.generated.h"

// 퀘스트의 고유넘버
UENUM(BlueprintType)
enum class EQuestCode : uint8
{
	EQC_0001 UMETA(DisplayName = "0001"),
	EQC_0002 UMETA(DisplayName = "0002"),
	EQC_None UMETA(DisplayName = "None"),
};

// 퀘스트 상태
UENUM(BlueprintType)
enum class EQuestState : uint8
{
	EQS_Progress UMETA(DisplayName = "Progress"),
	EQS_Complete UMETA(DisplayName = "Complete"),
	EQS_None UMETA(DisplayName = "None"),
};

// 아이템 수집에 관한 조건 (몇 개의 아이템이 필요한가?)
USTRUCT(BlueprintType)
struct FItemCondition
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemCode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAmount;
};

// 적 처치에 관한 조건 (몇 마리를 죽여야 하나?)
USTRUCT(BlueprintType)
struct FEnemyCondition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EnemyCode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentKillCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxKillCount;
};

// 완료 후 보상
USTRUCT(BlueprintType)
struct FQuestReward
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Exp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Gold;

	// 어떤 아이템을 몇개 지급하는지?
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, int32> ItemMap;
};

USTRUCT(BlueprintType)
struct FQuest : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	// 퀘스트 제목
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Title;

	// 대화 내용
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> Dialogue;

	// 요약
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Summary;

	// 수락 가능 레벨
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;

	// 수집에 관한 조건들
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FItemCondition> ItemConditions;

	// 처치에 관한 조건들
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FEnemyCondition> EnemyConditions;

	// 보상
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FQuestReward QuestReward;
};