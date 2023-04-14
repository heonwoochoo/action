﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/SubMenu.h"
#include "StartMenu.generated.h"

class UButton;
class UImage;
class UStackBox;
class UTexture2D;

UCLASS()
class PORTFOLIO_API UStartMenu : public USubMenu
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* NewImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* NewButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* LoadImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DeleteImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DeleteButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UStackBox* SavedGameBox;

	// 텍스처
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedBox;

	// ==========================
	//		이벤트 발생시 호출
	// ==========================

	UFUNCTION()
	void OnHoveredNewButton();

	UFUNCTION()
	void OnUnhoveredNewButton();

	UFUNCTION()
	void OnClickedNewButton();

	UFUNCTION()
	void OnHoveredLoadButton();

	UFUNCTION()
	void OnUnhoveredLoadButton();

	UFUNCTION()
	void OnClickedLoadButton();

	UFUNCTION()
	void OnHoveredDeleteButton();

	UFUNCTION()
	void OnUnhoveredDeleteButton();

	UFUNCTION()
	void OnClickedDeleteButton();

private:
	void InitNewButton();
	void InitLoadButton();
	void InitDeleteButton();
};
