// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UMainMenu;
class UOptionsWidget;

UCLASS()
class PORTFOLIO_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 뒤로가기 버튼 (메인메뉴로 돌아가기)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ActiveBackButtonImage;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedArrowLeft;

	// 메인메뉴 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UMainMenu> MainMenuClass;

	// 옵션 메뉴 생성시 표시될 옵션 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UOptionsWidget> OptionClass;

	// 현재 표시된 옵션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	UOptionsWidget* SelectedOption;


	// ==========================
	//		이벤트 발생시 호출
	// ==========================

	// Back
	UFUNCTION()
	void OnHoveredBackButton();

	UFUNCTION()
	void OnUnhoveredBackButton();

	UFUNCTION()
	void OnClickedBackButton();

private:
	void InitBack();
	
public:
	void SetSelectedOption(UOptionsWidget* Widget);
};
