// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExitBox.generated.h"

class UImage;
class UButton;


UCLASS()
class PORTFOLIO_API UExitBox : public UUserWidget
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
	UImage* ReturnSMenuImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ReturnSMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ExitGamelImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CancelImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CancelButton;

	UFUNCTION()
	void OnHoveredReturnSMenuButton();

	UFUNCTION()
	void OnUnhoveredReturnSMenuButton();

	UFUNCTION()
	virtual void OnClickedReturnSMenuButton();

	UFUNCTION()
	void OnHoveredExitGameButton();

	UFUNCTION()
	void OnUnhoveredExitGameButton();

	UFUNCTION()
	virtual void OnClickedExitGameButton();

	UFUNCTION()
	void OnHoveredCancelButton();

	UFUNCTION()
	void OnUnhoveredCancelButton();

	UFUNCTION()
	void OnClickedCancelButton();

private:
	void InitReturnSMenuButton();
	void InitExitGameButton();
	void InitCancelButton();

	// OK, Cancel 버튼 클릭시 재생
	void PlayButtonSound();
};
