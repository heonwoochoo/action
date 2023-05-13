// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/InGame/MovableWidget.h"
#include "Types/SettingTypes.h"
#include "Types/QuestTypes.h"
#include "QuestInfo.generated.h"

class UTextBlock;
class UVerticalBox;
class UQuestHeadline;
class UQuestDetail;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedQuestSignature, const EQuestCode&, InQuestCode);

UCLASS()
class PORTFOLIO_API UQuestInfo : public UMovableWidget
{
	GENERATED_BODY()
	
public:
	FOnClickedQuestSignature OnClicked;
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* ProgressTabOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ProgressTabBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ProgressTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ProgressTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ProgressTabUnderline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* CompleteTabOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CompleteTabBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CompleteTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CompleteTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CompleteTabUnderline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* QuestBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UQuestDetail* QuestDetail;

	// 박스 안에 담길 퀘스트 제목의 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UQuestHeadline> QuestHeadlineClass;

private:
	// 클라이언트가 가지고 있는 퀘스트 정보
	TArray<FQuestClientData> QuestList;

	// 클릭으로 현재 선택된 퀘스트
	EQuestCode SelectedQuest = EQuestCode::EQC_None;

public:
	UFUNCTION()
	void OnChangedInputMode(const EInputMode& Mode);

	FORCEINLINE EQuestCode GetSelectedQuest() const { return SelectedQuest; }
	FORCEINLINE void SetSelectedQuest(const EQuestCode& InQuest) { SelectedQuest = InQuest; }

};