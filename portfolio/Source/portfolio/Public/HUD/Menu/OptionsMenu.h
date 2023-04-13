// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UMainMenu;
class UTextBlock;
class UProgressBar;
class USlider;

UCLASS()
class PORTFOLIO_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 뒤로가기 버튼 (메인메뉴로 돌아가기)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ActiveBackButtonImage;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedArrowRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedArrowRight;

	// 메인메뉴 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UMainMenu> MainMenuClass;

	// =============================
	//         그래픽 옵션
	// =============================

	// Window Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* WindowModeOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* WindowModeOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* WindowModeButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* WindowModeButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WindowModeSetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* WindowModeButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* WindowModeButtonRightArrow;



	// Display Resolution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DisplayResolutionOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DisplayResolutionOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DisplayResolutionButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DisplayResolutionButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DisplayResolutionSetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DisplayResolutionButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DisplayResolutionButtonRightArrow;



	// Post Processing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PostProcessingOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PostProcessingOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PostProcessingButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PostProcessingButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PostProcessingSetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PostProcessingButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PostProcessingButtonRightArrow;



	// Anti Aliasing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* AntiAliasingOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* AntiAliasingOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* AntiAliasingButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* AntiAliasingButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AntiAliasingSetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* AntiAliasingButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* AntiAliasingButtonRightArrow;



	// Texture Quality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TextureQualityOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TextureQualityOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TextureQualityButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TextureQualityButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextureQualitySetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TextureQualityButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TextureQualityButtonRightArrow;



	// Shadow Quality
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ShadowQualityOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ShadowQualityOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ShadowQualityButtonLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ShadowQualityButtonLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShadowQualitySetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ShadowQualityButtonRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ShadowQualityButtonRightArrow;



	// Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SoundOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SoundOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* SoundProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* SoundSlider;



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

	// ==========================
	//		이벤트 발생시 호출
	// ==========================

	// Back
	UFUNCTION()
	void OnHoveredBackButton();

	UFUNCTION()
	void OnUnhoveredBackButton();

	UFUNCTION()
	void OnClickedBackButton();

	// Window Mode
	UFUNCTION()
	void OnHoveredWindowMode();

	UFUNCTION()
	void OnUnhoveredWindowMode();

	UFUNCTION()
	void OnHoveredWindowModeArrowLeft();

	UFUNCTION()
	void OnUnhoveredWindowModeArrowLeft();

	UFUNCTION()
	void OnHoveredWindowModeArrowRight();

	UFUNCTION()
	void OnUnhoveredWindowModeArrowRight();

	// Display Resolution
	UFUNCTION()
	void OnHoveredDisplayResolution();

	UFUNCTION()
	void OnUnhoveredDisplayResolution();

	UFUNCTION()
	void OnHoveredDisplayResolutionArrowLeft();

	UFUNCTION()
	void OnUnhoveredDisplayResolutionArrowLeft();

	UFUNCTION()
	void OnHoveredDisplayResolutionArrowRight();

	UFUNCTION()
	void OnUnhoveredDisplayResolutionArrowRight();

	// Post Processing
	UFUNCTION()
	void OnHoveredPostProcessing();

	UFUNCTION()
	void OnUnhoveredPostProcessing();

	UFUNCTION()
	void OnHoveredPostProcessingArrowLeft();

	UFUNCTION()
	void OnUnhoveredPostProcessingArrowLeft();

	UFUNCTION()
	void OnHoveredPostProcessingArrowRight();

	UFUNCTION()
	void OnUnhoveredPostProcessingArrowRight();

	// Anti Aliasing
	UFUNCTION()
	void OnHoveredAntiAliasing();

	UFUNCTION()
	void OnUnhoveredAntiAliasing();

	UFUNCTION()
	void OnHoveredAntiAliasingArrowLeft();

	UFUNCTION()
	void OnUnhoveredAntiAliasingArrowLeft();

	UFUNCTION()
	void OnHoveredAntiAliasingArrowRight();

	UFUNCTION()
	void OnUnhoveredAntiAliasingArrowRight();

	// Texture Quality
	UFUNCTION()
	void OnHoveredTextureQuality();

	UFUNCTION()
	void OnUnhoveredTextureQuality();

	UFUNCTION()
	void OnHoveredTextureQualityArrowLeft();

	UFUNCTION()
	void OnUnhoveredTextureQualityArrowLeft();

	UFUNCTION()
	void OnHoveredTextureQualityArrowRight();

	UFUNCTION()
	void OnUnhoveredTextureQualityArrowRight();

	// Shadow Quality
	UFUNCTION()
	void OnHoveredShadowQuality();

	UFUNCTION()
	void OnUnhoveredShadowQuality();

	UFUNCTION()
	void OnHoveredShadowQualityArrowLeft();

	UFUNCTION()
	void OnUnhoveredShadowQualityArrowLeft();

	UFUNCTION()
	void OnHoveredShadowQualityArrowRight();

	UFUNCTION()
	void OnUnhoveredShadowQualityArrowRight();

	// Sound
	UFUNCTION()
	void OnHoveredSound();

	UFUNCTION()
	void OnUnhoveredSound();


private:
	void InitBack();
	void InitWindowMode();
	void InitDisplayResolution();
	void InitPostProcessing();
	void InitAntiAliasing();
	void InitTextureQuality();
	void InitShadowQuality();
	void InitSound();
};
