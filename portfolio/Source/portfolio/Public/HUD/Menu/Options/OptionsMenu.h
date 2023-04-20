// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/Start/SubMenu.h"
#include "OptionsMenu.generated.h"

class UImage;
class UOptionsWidget;

UCLASS()
class PORTFOLIO_API UOptionsMenu : public USubMenu
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	// 옵션 메뉴 생성시 첫 페이지에 표시될 옵션 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UOptionsWidget> OptionClass;

	// 현재 표시된 옵션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	UOptionsWidget* SelectedOption;

	virtual void OnClickedBackButton() override;

public:
	void SetSelectedOption(UOptionsWidget* Widget);

	void HideBackgroundImage();
};