// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UOptionsMenu;

UCLASS()
class PORTFOLIO_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedSmallArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedSmallArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedSmallArrowRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedSmallArrowRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedLargeArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedLargeArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedLargeArrowRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedLargeArrowRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedBox;

	// Reset Button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ResetImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetButton;

	// Confirm Button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ConfirmImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConfirmButton;

	// Option Change
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionLeftButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OptionLeftImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionRightButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OptionRightImage;

	// OptionsMenu Widget
	UOptionsMenu* OptionsMenu;

	// 다음으로 넘겼을 때 표시될 옵션 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UOptionsWidget> OptionsWidgetClass;

	// ==========================
	//		이벤트 바인딩
	// ==========================
	// Reset
	UFUNCTION()
	void OnHoveredReset();

	UFUNCTION()
	void OnUnhoveredReset();

	// Confirm
	UFUNCTION()
	void OnHoveredConfirm();

	UFUNCTION()
	void OnUnhoveredConfirm();

	// Option Change
	UFUNCTION()
	void OnHoveredOptionLeftButton();

	UFUNCTION()
	void OnUnhoveredOptionLeftButton();

	UFUNCTION()
	void OnHoveredOptionRightButton();

	UFUNCTION()
	void OnUnhoveredOptionRightButton();

	UFUNCTION()
	void OnClickedOptionChangeButton();

private:
	void InitReset();
	void InitConfirm();
	void InitOptionChangeButton();

public:
	void SetOptionsMenu(UOptionsMenu* Widget);
};
