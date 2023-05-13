// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/QuestTypes.h"
#include "QuestHeadline.generated.h"

class UImage;
class UTextBlock;
class UTexture2D;
class UQuestInfo;
class UButton;

UCLASS()
class PORTFOLIO_API UQuestHeadline : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* HeadlineImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HeadlineText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HeadlineButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedImage;

	UFUNCTION()
	void OnHoveredHeadlineButton();

	UFUNCTION()
	void OnUnhoveredHeadlineButton();

	UFUNCTION()
	void OnClickedHeadlineButton();

private:
	// 퀘스트 정보 창
	UQuestInfo* QuestInfo;

	// 퀘스트 코드
	EQuestCode QuestCode = EQuestCode::EQC_None;

	void InitHeadlineButton();

public:
	FORCEINLINE UQuestInfo* GetQuestInfo() const { return QuestInfo; }
	FORCEINLINE void SetQuestInfo(UQuestInfo* InQuestInfo) { QuestInfo = InQuestInfo; }

	FORCEINLINE EQuestCode GetQuestCode() const { return QuestCode; }
	FORCEINLINE void SetQuestCode(const EQuestCode& InQuestCode) { QuestCode = InQuestCode; }

	void SetHeadlineText(const FText& InText);

	// 선택 유무에 따라 헤드라인의 배경 이미지 변화
	UFUNCTION()
	void OnClickedQuest(const EQuestCode& InCode);
};
