// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuestTypes.h"
#include "Types/EnemyTypes.h"
#include "QuestClientComponent.generated.h"

class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedQuestStateSignature, const EQuestCode&, InQuestCode, const EQuestState&, NewState);

/**
* 클라이언트가 NPC로부터 수락한 퀘스트 정보를 나타냅니다.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UQuestClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestClientComponent();

	FOnChangedQuestStateSignature OnChangedState;

protected:
	virtual void BeginPlay() override;

	// 퀘스트 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FQuestClientData> QuestList;

	// 클리어한 퀘스트 목록
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<EQuestCode> ClearedQuests;

	// 퀘스트 수락시 효과음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundCue* QuestAcceptSound;

	// 퀘스트 완료시 효과음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundCue* QuestClearSound;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 저장된 퀘스트 데이터를 불러옵니다
	void LoadDataFromSaveGame();

	// 퀘스트를 클라이언트의 리스트에 추가
	void AddQuest(const EQuestCode& InQuestCode, const FQuest& InQuest);

	// 클라이언트의 퀘스트를 클리어
	void ClearQuest(const EQuestCode& InQuestCode);

	FORCEINLINE TArray<FQuestClientData> GetQuestList() const { return QuestList; }
	FORCEINLINE void SetQuestList(const TArray<FQuestClientData>& InQuestList) { QuestList = InQuestList; }

	FORCEINLINE TArray<EQuestCode> GetClearedQuests() const { return ClearedQuests; }
	FORCEINLINE void SetClearedQuests(const TArray<EQuestCode>& InClearedQuests) { ClearedQuests = InClearedQuests; }

	UFUNCTION()
	void AddEnemyKillCount(const FName& InEnemyCode, const int32& InCount);

	bool IsExistEnemyInQuestList(const FName& InEnemyCode);

	
};