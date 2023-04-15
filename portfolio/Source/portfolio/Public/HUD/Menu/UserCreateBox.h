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

private:
	void InitOKButton();
	void InitCancelButton();

	void PlayButtonSound();
};
