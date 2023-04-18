// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenu.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UMainMenu;

UCLASS()
class PORTFOLIO_API USubMenu : public UUserWidget
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

	// ==========================
	//		이벤트 발생시 호출
	// ==========================

	// Back
	UFUNCTION()
	void OnHoveredBackButton();

	UFUNCTION()
	void OnUnhoveredBackButton();

	UFUNCTION()
	virtual void OnClickedBackButton();

private:
	void InitBack();

public:
	void PlayButtonSound();
};
