// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/CharacterTypes.h"
#include "Types/ItemTypes.h"
#include "Types/QuestTypes.h"
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

	// 위치
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform Transform;

	// 스탯
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCharacterStats Stats;

	// 직업
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterClass Class;

	// 무기 장착 상태
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterEquipState EquipState = ECharacterEquipState::ECES_Unquipped;

	/**
	* 인벤토리 컴포넌트
	*/
	// 장착한 아이템 상태
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EEquipmentType, FEquippedItem> EquippedItemList;

	// 장착중인 무기
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EquippedWeaponCode;

	// 저장되어 있는 아이템
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, uint8> ItemList;

	/**
	* 퀘스트 클라이언트 컴포넌트
	*/
	// 퀘스트
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FQuestClientData> QuestList;

	// 클리어한 퀘스트 목록
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EQuestCode> ClearedQuests;
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
