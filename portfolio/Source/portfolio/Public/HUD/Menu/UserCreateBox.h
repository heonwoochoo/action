// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/TwoButtonWidget.h"
#include "UserCreateBox.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UEditableTextBox;
class UTextBlock;
class UStartMenu;

UCLASS()
class PORTFOLIO_API UUserCreateBox : public UTwoButtonWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* UsernameTextBox;

	UFUNCTION()
	void OnChangedEnterText(const FText& Text);

	virtual void OnClickedOKButton() override;

private:
	//============================================================
	//   유저 이름 입력 관련 변수
	//============================================================
	// 최소 글자 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	int32 MinUserNameLength = 3;

	// 최대 글자 수 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	int32 MaxUserNameLength = 15;

	// 글자수 미달 에러 메세지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName ShortLengthMessage;

	// 글자수 초과 에러 메세지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName ExceedMaxLengthMessage;

	// 공백 입력 에러 메세지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName WhiteSpaceMessage;

	// 영문만 입력하세요 에러 메세지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName NeedAlphaMessage;

	// 이미 존재하는 이름입니다 에러 메세지
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName ExistNameMessage;

	// 유효한 이름인가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	bool bIsValidUserName = false;
	

	// 입력으로 들어온 문자열 검사, 유효하지 않은 문자 입력시 에러 메세지 나타냄
	void CheckIsValidUserName(const FText& Text);

	// 이미 존재하는 유저인지 세이브 파일 확인
	void CheckExistUserName(const FText& Text);

	//==============================================================
	// StartMenu 인스턴스
	UStartMenu* StartMenu;

	// UI 생성시 호출
	void InitUsernameTextBox();

public:
	void SetStartMenu(UStartMenu* UserWidget);
};
