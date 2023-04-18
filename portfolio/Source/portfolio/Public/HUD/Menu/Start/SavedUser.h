// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SavedUser.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UStartMenu;

UCLASS()
class PORTFOLIO_API USavedUser : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SelectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ListNumberText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UserNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CreatedDateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RecentDateText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayTimeText;

	UFUNCTION()
	void OnHoveredSelectButton();

	UFUNCTION()
	void OnUnhoveredSelectButton();

	UFUNCTION()
	void OnClickedSelectButton();

	UFUNCTION()
	void ChangeTextColor(FColor Color);

private:
	// 생성넘버
	int32 ListNumber;

	// 유저 이름
	FText UserName;

	// 생성 날짜
	FDateTime CreatedDate;

	// 마지막 플레이 날짜
	FDateTime RecentDate;

	// 플레이 타임 (초)
	float PlayTime;

	// 클릭시 True
	bool IsSelected = false;

	// 인스턴스 생성시 이벤트 함수 등록
	void InitSelectButton();

	void PlaySelectButtonClickSound();

	// 스타트 메뉴 인스턴스
	UStartMenu* StartMenu;

	// Date 타입을 날짜형식 String 타입으로 변환
	FString TransformDateToString(FDateTime Date);

public:
	// 다른 유저 선택시 체크 옵션 해제
	void UnCheckedButton();

	void SetStartMenu(UStartMenu* UserWidget);

	FText GetUserName() const;
	void SetUserName(FText Name);

	void SetListNumber(int32 Num);

	void SetCreatedDate(FDateTime Date);

	void SetRecentDate(FDateTime Date);

	void SetPlayTime(float Seconds);
};
