// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuestTypes.h"
#include "NPCDialogueComponent.generated.h"

class UDialogueBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UNPCDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNPCDialogueComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 다이얼로그가 열린 퀘스트의 코드
	EQuestCode QuestCode = EQuestCode::EQC_None;

	// 대화창 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDialogueBox> DialogueBoxClass;

	// 생성된 대화창 위젯
	UDialogueBox* DialogueBox;

	// 다이얼로그 텍스트
	TArray<FText> DialogueText;

	// 다이얼로그의 현재 페이지
	int32 CurrentPage = 0;

	// 다이얼로그의 마지막 페이지
	int32 LastPage = 0;

public:	
	void OpenDialogueBox(const TArray<FText>& InDialogueText);
	
	// 첫 페이지 열기
	void OpenFirstPage();

	// 다음 페이지로 이동
	void ReadNextPage();

	// 이전 페이지로 이동
	void ReadPrevPage();

	FORCEINLINE int32 GetCurrentPage() const { return CurrentPage; }
	FORCEINLINE int32 GetLastPage() const { return LastPage; }

	FORCEINLINE EQuestCode GetQuestCode() const { return QuestCode; }
	FORCEINLINE void SetQuestCode(const EQuestCode& InQuestCode) { QuestCode = InQuestCode; }
};