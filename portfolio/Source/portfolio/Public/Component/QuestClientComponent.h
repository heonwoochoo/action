// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuestTypes.h"
#include "QuestClientComponent.generated.h"

class USoundCue;

/**
* 클라이언트가 NPC로부터 수락한 퀘스트 정보를 나타냅니다.
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UQuestClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestClientComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FQuestClientData> QuestList;

	// 퀘스트 수락시 효과음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundCue* QuestAcceptSound;

	// 퀘스트 완료시 효과음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundCue* QuestClearSound;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 퀘스트를 클라이언트의 리스트에 추가
	void AddQuest(const EQuestCode& InQuestCode, const FQuest& InQuest);
};