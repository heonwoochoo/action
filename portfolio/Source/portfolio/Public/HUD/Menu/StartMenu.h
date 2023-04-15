﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/SubMenu.h"
#include "StartMenu.generated.h"

class UButton;
class UImage;
class UStackBox;
class UTexture2D;
class UUserCreateBox;
class USavedUser;

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

	// 유저 생성 창 UI 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UUserCreateBox> UserCreateBoxClass;

	// 유저 생성 UI 인스턴스
	UUserCreateBox* UserCreateBox;

	// 리스트에 들어갈 UI 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<USavedUser> SavedUserClass;

	// 저장된 유저 위젯 리스트
	TArray<USavedUser*> SavedUserList;

	// 현재 선택된 유저
	USavedUser* SelectedUser;

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

	virtual void OnClickedBackButton() override;

private:
	void InitNewButton();
	void InitLoadButton();
	void InitDeleteButton();

	void LoadUserNameFromSaveGame();
public:
	void AddUser(const FText UserName);
	
	USavedUser* GetSelectedUser() const;
	void SetSelectedUser(USavedUser* SavedUser);
};
