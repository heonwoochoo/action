// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovableWidget.generated.h"

class UCanvasPanel;
class UTexture2D;
class UOverlay;
class UButton;
class UImage;

UCLASS()
class PORTFOLIO_API UMovableWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* InnerCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* TitleDragOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TitleTextImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TitleDragButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ExitButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedTitleBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedTitleBox;

	UFUNCTION()
	void OnHoveredTitleDragButton();

	UFUNCTION()
	void OnUnhoveredTitleDragButton();

	UFUNCTION()
	void OnPressedTitleDragButton();

	UFUNCTION()
	virtual void OnReleasedTitleDragButton();

	UFUNCTION()
	void OnHoveredExitButton();

	UFUNCTION()
	void OnUnhoveredExitButton();

	UFUNCTION()
	void OnClickedExitButton();
	
	void PlayButtonSound();

	// 오픈시 저장된 위치 값 불러오기
	virtual void InitCanvasLocation();

	// 버튼 Press,Release 이벤트로 토글
	// true시 인벤토리 창이 마우스 따라 이동
	bool bCanMovable = false;

	// 마우스와 캔버스의 간격
	float OffsetX;
	float OffsetY;

private:
	void InitTitleDragButton();
	void InitExitButton();
	
};
