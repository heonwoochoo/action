﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

class UButton;
class UImage;
class UWidgetAnimation;
class UExitBox;

UCLASS()
class PORTFOLIO_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* AnimShowMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* AnimHideMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CharacterButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CharacterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* InventoryButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* InventoryButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* QuestButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuestButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SettingsButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SaveButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ExitButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	// Exit 버튼을 누르면 나오는 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu")
	TSubclassOf<UExitBox> ExitBoxClass;

	// 생성된 Exit 위젯 인스턴스
	UExitBox* ExitBox;

	//====================
	// 이벤트 발생시 호출
	//====================
	
	UFUNCTION()
	void OnHoveredCharacterButton();

	UFUNCTION()
	void OnUnhoveredCharacterButton();

	UFUNCTION()
	void OnClickedCharacterButton();

	UFUNCTION()
	void OnHoveredInventoryButton();

	UFUNCTION()
	void OnUnhoveredInventoryButton();

	UFUNCTION()
	void OnClickedInventoryButton();

	UFUNCTION()
	void OnHoveredQuestButton();

	UFUNCTION()
	void OnUnhoveredQuestButton();

	UFUNCTION()
	void OnClickedQuestButton();

	UFUNCTION()
	void OnHoveredSettingsButton();

	UFUNCTION()
	void OnUnhoveredSettingsButton();

	UFUNCTION()
	void OnClickedSettingsButton();

	UFUNCTION()
	void OnHoveredSaveButton();

	UFUNCTION()
	void OnUnhoveredSaveButton();

	UFUNCTION()
	void OnClickedSaveButton();

	UFUNCTION()
	void OnHoveredExitButton();

	UFUNCTION()
	void OnUnhoveredExitButton();

	UFUNCTION()
	void OnClickedExitButton();

private:
	void InitCharacterButton();
	void InitInventoryButton();
	void InitQuestButton();
	void InitSettingsButton();
	void InitSaveButton();
	void InitExitButton();

public:
	void PlayShowAnimation();
	void PlayHideAnimation();

	// Hide 애니메이션 종료 시 호출
	// 메뉴 창을 닫음
	UFUNCTION()
	void OnEndHideAnimation();

	// 버튼 클릭 사운드 재생
	void PlayButtonSound();

	FWidgetAnimationDynamicEvent EndAnimationEvent;

	// 열려있는 창 제거 (인벤토리, 캐릭터, ...)
	void RemoveOpenedWidget();
};