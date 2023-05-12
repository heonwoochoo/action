// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/QuestTypes.h"
#include "QuestSelectBoxList.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedQuestSignature, const EQuestCode&, SelectedCode);

UCLASS()
class PORTFOLIO_API UQuestSelectBoxList : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	FOnSelectedQuestSignature OnSelected;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ListButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ArrowImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HeadlineText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StateText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Textrue")
	UTexture2D* ActivatedArrowRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Textrue")
	UTexture2D* DeactivatedArrowRight;

	// 해당 리스트의 고유한 퀘스트 코드
	EQuestCode QuestCode = EQuestCode::EQC_None;

public:
	UFUNCTION()
	void OnHoveredListButton();

	UFUNCTION()
	void OnUnhoveredListButton();

	UFUNCTION()
	void OnClickedListButton();

	// 제목 텍스트 설정
	void SetHeadlineText(const FText& InTitle);

	// 상태 텍스트 설정
	void SetStateText(const EQuestState& InState);

	FORCEINLINE EQuestCode GetQuestCode() const { return QuestCode; }
	FORCEINLINE void SetQuestCode(const EQuestCode& InCode) { QuestCode = InCode; }


private:
	// 해당 리스트가 선택되었는지 여부 (클릭으로 토글)
	bool bIsSelected = false;

	void InitListButton();
};