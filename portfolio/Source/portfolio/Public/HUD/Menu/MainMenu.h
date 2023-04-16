﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UImage;
class UTexture2D;
class USubMenu;

UCLASS()
class PORTFOLIO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* StartButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OptionsButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CreditsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CreditsButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* QuitButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<USubMenu> StartMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<USubMenu> OptionsMenuClass;

	UFUNCTION()
	void OnHoveredStartButton();

	UFUNCTION()
	void OnUnhoveredStartButton();

	UFUNCTION()
	void OnClickedStartButton();

	UFUNCTION()
	void OnHoveredOptionsButton();

	UFUNCTION()
	void OnUnhoveredOptionsButton();

	UFUNCTION()
	void OnClickedOptionsButton();

	UFUNCTION()
	void OnHoveredCreditsButton();

	UFUNCTION()
	void OnUnhoveredCreditsButton();

	UFUNCTION()
	void OnClickedCreditsButton();

	UFUNCTION()
	void OnHoveredQuitButton();

	UFUNCTION()
	void OnUnhoveredQuitButton();

	UFUNCTION()
	void OnClickedQuitButton();

private:
	void InitStartButton();
	void InitOptionsButton();
	void InitCreditsButton();
	void InitQuitButton();

	void PlayButtonClickSound();
};
