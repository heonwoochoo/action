// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/OptionsWidget.h"
#include "OptionsGraphic.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UMainMenu;
class UTextBlock;
class UOptionsMenu;
class UGameUserSettings;

struct FGraphicSetting
{
	EWindowMode::Type WindowMode;

	int32 ResolutionLevel;
};

UCLASS()
class PORTFOLIO_API UOptionsGraphic : public UOptionsWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

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

	// ==========================
	//		이벤트 바인딩
	// ==========================

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
	void OnClickedWindowModeArrowLeft();

	UFUNCTION()
	void OnHoveredWindowModeArrowRight();

	UFUNCTION()
	void OnUnhoveredWindowModeArrowRight();

	UFUNCTION()
	void OnClickedWindowModeArrowRight();

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
	void OnClickedDisplayResolutionArrowLeft();

	UFUNCTION()
	void OnHoveredDisplayResolutionArrowRight();

	UFUNCTION()
	void OnUnhoveredDisplayResolutionArrowRight();

	UFUNCTION()
	void OnClickedDisplayResolutionArrowRight();

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
	void OnClickedPostProcessingArrowLeft();

	UFUNCTION()
	void OnHoveredPostProcessingArrowRight();

	UFUNCTION()
	void OnUnhoveredPostProcessingArrowRight();

	UFUNCTION()
	void OnClickedPostProcessingArrowRight();

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
	void OnClickedAntiAliasingArrowLeft();

	UFUNCTION()
	void OnHoveredAntiAliasingArrowRight();

	UFUNCTION()
	void OnUnhoveredAntiAliasingArrowRight();

	UFUNCTION()
	void OnClickedAntiAliasingArrowRight();

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
	void OnClickedTextureQualityArrowLeft();

	UFUNCTION()
	void OnHoveredTextureQualityArrowRight();

	UFUNCTION()
	void OnUnhoveredTextureQualityArrowRight();

	UFUNCTION()
	void OnClickedTextureQualityArrowRight();

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
	void OnClickedShadowQualityArrowLeft();

	UFUNCTION()
	void OnHoveredShadowQualityArrowRight();

	UFUNCTION()
	void OnUnhoveredShadowQualityArrowRight();

	UFUNCTION()
	void OnClickedShadowQualityArrowRight();

	// Reset , Confirm
	virtual void OnClickedReset() override;
	virtual void OnClickedConfirm() override;

private:
	UGameUserSettings* UserSettings;

	// 컨펌시 그래픽 세팅을 위한 데이터를 저장하고 있는 변수
	// UI 생성시 현재 세팅 값을 초기값으로 복사함
	FGraphicSetting Settings;

	// 초기화를 위해 UI 생성 당시의 세팅 값을 저장
	FGraphicSetting ResetSettings;

	//==========================
	//		WindowMode
	//==========================
	void InitWindowMode();
	FText GetWindowModeText(EWindowMode::Type Mode);

	//==========================
	//    Display Resoultion
	//==========================
	void InitDisplayResolution();
	FIntPoint GetResolutionFromInt(int32 num);
	int32 GetIntFromResolution(FIntPoint Resolution);
	FText GetTextFromResolution(FIntPoint Resolution);

	void ChangeLevel(int32* OptionLevel, bool IsIncrease);


	
	void InitPostProcessing();
	void InitAntiAliasing();
	void InitTextureQuality();
	void InitShadowQuality();

};
