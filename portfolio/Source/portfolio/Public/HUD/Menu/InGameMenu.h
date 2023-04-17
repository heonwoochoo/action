// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

class UButton;
class UImage;
class UWidgetAnimation;

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
	UImage* ExitButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

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
	void InitExitButton();

public:
	void PlayShowAnimation();
	void PlayHideAnimation();

	// Hide 애니메이션 종료 시 호출
	// 메뉴 창을 닫음
	void OnEndHideAnimation();

	FWidgetAnimationDynamicEvent EndAnimationEvent;
};
