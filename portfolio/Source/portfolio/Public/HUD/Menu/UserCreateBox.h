// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserCreateBox.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UEditableTextBox;
class UTextBlock;
class UStartMenu;

UCLASS()
class PORTFOLIO_API UUserCreateBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ErrorMessageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* UsernameTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OKImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OKButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CancelImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CancelButton;

	UFUNCTION()
	void OnHoveredOKButton();

	UFUNCTION()
	void OnUnhoveredOKButton();

	UFUNCTION()
	void OnClickedOKButton();

	UFUNCTION()
	void OnHoveredCancelButton();

	UFUNCTION()
	void OnUnhoveredCancelButton();

	UFUNCTION()
	void OnClickedCancelButton();

	UFUNCTION()
	void OnChangedEnterText(const FText& Text);

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

	// 영문만 입력하세요
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	FName NeedAlphaMessage;

	// 유효한 이름인가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserName", meta = (AllowPrivateAccess = "true"))
	bool bIsValidUserName = false;

	// 입력으로 들어온 문자열 검사, 유효하지 않은 문자 입력시 에러 메세지 나타냄
	void CheckIsValidUserName(const FText& Text);

	//==============================================================

	// StartMenu 인스턴스
	UStartMenu* StartMenu;

	// UI 생성시 호출
	void InitUsernameTextBox();
	void InitOKButton();
	void InitCancelButton();

	// OK, Cancel 버튼 클릭시 재생
	void PlayButtonSound();

public:
	void SetStartMenu(UStartMenu* UserWidget);
};
