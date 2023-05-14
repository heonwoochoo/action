// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuestTypes.h"
#include "QuestServerComponent.generated.h"

class UDataTable;
class ADefaultCharacter;

/**
* NPC 캐릭터에 부착되어 퀘스트를 제공해주는 기능을 합니다.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UQuestServerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestServerComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 모든 퀘스트 정보가 들어있는 데이터 파일
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* QuestDataTable;

	// NPC가 소유하고 있는 퀘스트 목록과 상태
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EQuestCode, EQuestState> QuestList;

public:
	// 퀘스트 등록
	void AddQuest(const EQuestCode& InQuestCode);

	// 퀘스트 클리어
	void ClearQuest(const EQuestCode& InQuestCode, ADefaultCharacter* PlayerCharacter);

	// 퀘스트 코드를 참조하여 데이터를 반환
	FQuest* GetQuestData(const EQuestCode& InQuestCode);

	FORCEINLINE TMap<EQuestCode, EQuestState> GetQuestList() const { return QuestList; }
	
	// 리스트에 있는 퀘스트의 상태를 변경
	void SetQuestStateInList(const EQuestCode& TargetQuest, const EQuestState& InState);

	// 퀘스트를 플레이어에게 제공합니다.
	void ServeQuestToPlayer(const EQuestCode& QuestCode);

	UFUNCTION()
	void OnChangedClientQuestState(const EQuestCode& InQuestCode, const EQuestState& NewState);

	// 클라이언트의 퀘스트 상태변경 구독 상태
	bool bDelegateClientOnChanged = false;
};