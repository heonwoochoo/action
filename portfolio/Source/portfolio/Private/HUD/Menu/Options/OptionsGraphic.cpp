// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/Menu/Options/OptionsGraphic.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/Options/OptionsMenu.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/TextBlock.h"

void UOptionsGraphic::NativeConstruct()
{
	Super::NativeConstruct();

	UserSettings = UGameUserSettings::GetGameUserSettings();

	InitWindowMode();
	InitDisplayResolution();
	InitPostProcessing();
	InitAntiAliasing();
	InitTextureQuality();
	InitShadowQuality();

	ResetSettings = Settings;
}

void UOptionsGraphic::OnHoveredWindowMode()
{
	if (WindowModeOverlayImage)
	{
		WindowModeOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredWindowMode()
{
	if (WindowModeOverlayImage)
	{
		WindowModeOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredWindowModeArrowLeft()
{
	if (WindowModeButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		WindowModeButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredWindowModeArrowLeft()
{
	if (WindowModeButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		WindowModeButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedWindowModeArrowLeft()
{
	EWindowMode::Type CurrentMode = Settings.WindowMode;
	EWindowMode::Type NextMode{};
	switch (CurrentMode)
	{
	case EWindowMode::Type::Fullscreen:
		NextMode = EWindowMode::Type::Windowed;
		break;
	case EWindowMode::Type::Windowed:
		NextMode = EWindowMode::Type::WindowedFullscreen;
		break;
	case EWindowMode::Type::WindowedFullscreen:
		NextMode = EWindowMode::Type::Fullscreen;
		break;
	}
	Settings.WindowMode = NextMode;
	WindowModeSetText->SetText(GetWindowModeText(NextMode));

	PlayChangeButtonSound();
}

void UOptionsGraphic::OnHoveredWindowModeArrowRight()
{
	if (WindowModeButtonRightArrow && ActivatedSmallArrowRight)
	{
		WindowModeButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredWindowModeArrowRight()
{
	if (WindowModeButtonRightArrow && DeactivatedSmallArrowRight)
	{
		WindowModeButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedWindowModeArrowRight()
{
	EWindowMode::Type CurrentMode = Settings.WindowMode;
	EWindowMode::Type NextMode{};
	switch (CurrentMode)
	{
	case EWindowMode::Type::Fullscreen:
		NextMode = EWindowMode::Type::WindowedFullscreen;
		break;
	case EWindowMode::Type::WindowedFullscreen:
		NextMode = EWindowMode::Type::Windowed;
		break;
	case EWindowMode::Type::Windowed:
		NextMode = EWindowMode::Type::Fullscreen;
		break;
	}
	Settings.WindowMode = NextMode;
	WindowModeSetText->SetText(GetWindowModeText(NextMode));

	PlayChangeButtonSound();
}

void UOptionsGraphic::OnHoveredDisplayResolution()
{
	if (DisplayResolutionOverlayImage)
	{
		DisplayResolutionOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredDisplayResolution()
{
	if (DisplayResolutionOverlayImage)
	{
		DisplayResolutionOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredDisplayResolutionArrowLeft()
{
	if (DisplayResolutionButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		DisplayResolutionButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredDisplayResolutionArrowLeft()
{
	if (DisplayResolutionButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		DisplayResolutionButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedDisplayResolutionArrowLeft()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.ResolutionLevel, false);

	FIntPoint Resolution = GetResolutionFromInt(Settings.ResolutionLevel);

	DisplayResolutionSetText->SetText(GetTextFromResolution(Resolution));
}

void UOptionsGraphic::OnHoveredDisplayResolutionArrowRight()
{
	if (DisplayResolutionButtonRightArrow && ActivatedSmallArrowRight)
	{
		DisplayResolutionButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredDisplayResolutionArrowRight()
{
	if (DisplayResolutionButtonRightArrow && DeactivatedSmallArrowRight)
	{
		DisplayResolutionButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedDisplayResolutionArrowRight()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.ResolutionLevel, true);

	FIntPoint Resolution = GetResolutionFromInt(Settings.ResolutionLevel);

	DisplayResolutionSetText->SetText(GetTextFromResolution(Resolution));
}

void UOptionsGraphic::OnHoveredPostProcessing()
{
	if (PostProcessingOverlayImage)
	{
		PostProcessingOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredPostProcessing()
{
	if (PostProcessingOverlayImage)
	{
		PostProcessingOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredPostProcessingArrowLeft()
{
	if (PostProcessingButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		PostProcessingButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredPostProcessingArrowLeft()
{
	if (PostProcessingButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		PostProcessingButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedPostProcessingArrowLeft()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.PostProcessingLevel, false);

	FText PostProcessingText = GetLevelTextFromInt(Settings.PostProcessingLevel);
	PostProcessingSetText->SetText(PostProcessingText);
}

void UOptionsGraphic::OnHoveredPostProcessingArrowRight()
{
	if (PostProcessingButtonRightArrow && ActivatedSmallArrowRight)
	{
		PostProcessingButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredPostProcessingArrowRight()
{
	if (PostProcessingButtonRightArrow && DeactivatedSmallArrowRight)
	{
		PostProcessingButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedPostProcessingArrowRight()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.PostProcessingLevel, true);

	FText PostProcessingText = GetLevelTextFromInt(Settings.PostProcessingLevel);
	PostProcessingSetText->SetText(PostProcessingText);
}

void UOptionsGraphic::OnHoveredAntiAliasing()
{
	if (AntiAliasingOverlayImage)
	{
		AntiAliasingOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredAntiAliasing()
{
	if (AntiAliasingOverlayImage)
	{
		AntiAliasingOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredAntiAliasingArrowLeft()
{
	if (AntiAliasingButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		AntiAliasingButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredAntiAliasingArrowLeft()
{
	if (AntiAliasingButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		AntiAliasingButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedAntiAliasingArrowLeft()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.AntiAliasingLevel, false);

	FText AntiAliasingText = GetLevelTextFromInt(Settings.AntiAliasingLevel);
	AntiAliasingSetText->SetText(AntiAliasingText);
}

void UOptionsGraphic::OnHoveredAntiAliasingArrowRight()
{
	if (AntiAliasingButtonRightArrow && ActivatedSmallArrowRight)
	{
		AntiAliasingButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredAntiAliasingArrowRight()
{
	if (AntiAliasingButtonRightArrow && DeactivatedSmallArrowRight)
	{
		AntiAliasingButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedAntiAliasingArrowRight()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.AntiAliasingLevel, true);

	FText AntiAliasingText = GetLevelTextFromInt(Settings.AntiAliasingLevel);
	AntiAliasingSetText->SetText(AntiAliasingText);
}

void UOptionsGraphic::OnHoveredTextureQuality()
{
	if (TextureQualityOverlayImage)
	{
		TextureQualityOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredTextureQuality()
{
	if (TextureQualityOverlayImage)
	{
		TextureQualityOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredTextureQualityArrowLeft()
{
	if (TextureQualityButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		TextureQualityButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredTextureQualityArrowLeft()
{
	if (TextureQualityButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		TextureQualityButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedTextureQualityArrowLeft()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.TextureQualityLevel, false);

	FText TextureQualityText = GetLevelTextFromInt(Settings.TextureQualityLevel);
	TextureQualitySetText->SetText(TextureQualityText);
}

void UOptionsGraphic::OnHoveredTextureQualityArrowRight()
{
	if (TextureQualityButtonRightArrow && ActivatedSmallArrowRight)
	{
		TextureQualityButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredTextureQualityArrowRight()
{
	if (TextureQualityButtonRightArrow && DeactivatedSmallArrowRight)
	{
		TextureQualityButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedTextureQualityArrowRight()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.TextureQualityLevel, true);

	FText TextureQualityText = GetLevelTextFromInt(Settings.TextureQualityLevel);
	TextureQualitySetText->SetText(TextureQualityText);
}

void UOptionsGraphic::OnHoveredShadowQuality()
{
	if (ShadowQualityOverlayImage)
	{
		ShadowQualityOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsGraphic::OnUnhoveredShadowQuality()
{
	if (ShadowQualityOverlayImage)
	{
		ShadowQualityOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsGraphic::OnHoveredShadowQualityArrowLeft()
{
	if (ShadowQualityButtonLeftArrow && ActivatedSmallArrowLeft)
	{
		ShadowQualityButtonLeftArrow->SetBrushFromTexture(ActivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnUnhoveredShadowQualityArrowLeft()
{
	if (ShadowQualityButtonLeftArrow && DeactivatedSmallArrowLeft)
	{
		ShadowQualityButtonLeftArrow->SetBrushFromTexture(DeactivatedSmallArrowLeft);
	}
}

void UOptionsGraphic::OnClickedShadowQualityArrowLeft()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.ShadowQualityLevel, false);

	FText ShadowQualityText = GetLevelTextFromInt(Settings.ShadowQualityLevel);
	ShadowQualitySetText->SetText(ShadowQualityText);
}

void UOptionsGraphic::OnHoveredShadowQualityArrowRight()
{
	if (ShadowQualityButtonRightArrow && ActivatedSmallArrowRight)
	{
		ShadowQualityButtonRightArrow->SetBrushFromTexture(ActivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnUnhoveredShadowQualityArrowRight()
{
	if (ShadowQualityButtonRightArrow && DeactivatedSmallArrowRight)
	{
		ShadowQualityButtonRightArrow->SetBrushFromTexture(DeactivatedSmallArrowRight);
	}
}

void UOptionsGraphic::OnClickedShadowQualityArrowRight()
{
	PlayChangeButtonSound();

	ChangeLevel(Settings.ShadowQualityLevel, true);

	FText ShadowQualityText = GetLevelTextFromInt(Settings.ShadowQualityLevel);
	ShadowQualitySetText->SetText(ShadowQualityText);
}

void UOptionsGraphic::OnClickedReset()
{
	Super::OnClickedReset();
	
	Settings = ResetSettings;

	// Window Mode
	WindowModeSetText->SetText(GetWindowModeText(Settings.WindowMode));

	// Display Resolution
	FIntPoint Resolution = GetResolutionFromInt(Settings.ResolutionLevel);
	DisplayResolutionSetText->SetText(GetTextFromResolution(Resolution));

	// Post Processing
	FText PostProcessingText = GetLevelTextFromInt(Settings.PostProcessingLevel);
	PostProcessingSetText->SetText(PostProcessingText);

	// Anti Aliasing
	FText AntiAliasingText = GetLevelTextFromInt(Settings.AntiAliasingLevel);
	AntiAliasingSetText->SetText(AntiAliasingText);

	// Texture Quality
	FText TextureQualityText = GetLevelTextFromInt(Settings.TextureQualityLevel);
	TextureQualitySetText->SetText(TextureQualityText);

	// Shadow Quality
	FText ShadowQualityText = GetLevelTextFromInt(Settings.ShadowQualityLevel);
	ShadowQualitySetText->SetText(ShadowQualityText);
}

void UOptionsGraphic::OnClickedConfirm()
{
	Super::OnClickedConfirm();
	
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(Settings.WindowMode);
		UserSettings->SetScreenResolution(GetResolutionFromInt(Settings.ResolutionLevel));
		UserSettings->SetPostProcessingQuality(Settings.PostProcessingLevel);
		UserSettings->SetAntiAliasingQuality(Settings.AntiAliasingLevel);
		UserSettings->SetTextureQuality(Settings.TextureQualityLevel);
		UserSettings->SetShadowQuality(Settings.ShadowQualityLevel);

		UserSettings->ApplySettings(false);
	}
}

FText UOptionsGraphic::GetWindowModeText(EWindowMode::Type Mode)
{
	FName ShowText{};
	switch (Mode)
	{
	case EWindowMode::Type::Fullscreen:
		ShowText = "Full";
		break;
	case EWindowMode::Type::Windowed:
		ShowText = "Windowed";
		break;
	case EWindowMode::Type::WindowedFullscreen:
		ShowText = "Windowed Full";
		break;
	default:
		ShowText = "UnKnowned";
		break;
	}
	return FText::FromName(ShowText);
}

FIntPoint UOptionsGraphic::GetResolutionFromInt(int32 num)
{
	FIntPoint Resolution{};

	switch (num)
	{
	case 0:
		Resolution.X = 720;
		Resolution.Y = 480;
		break;
	case 1:
		Resolution.X = 1280;
		Resolution.Y = 720;
		break;
	case 2:
		Resolution.X = 1920;
		Resolution.Y = 1080;
		break;
	case 3:
		Resolution.X = 2560;
		Resolution.Y = 1440;
		break;
	default:
		Resolution.X = 2560;
		Resolution.Y = 1440;
		break;
	}

	return Resolution;
}

int32 UOptionsGraphic::GetIntFromResolution(FIntPoint Resolution)
{
	int32 X = Resolution.X;
	int32 Y = Resolution.Y;

	if (X == (int32)2560 && Y == (int32)1440)
	{
		return 3;
	}
	else if (X == (int32)1920 && Y == (int32)1080)
	{
		return 2;
	}
	else if (X == (int32)1280 && Y == (int32)720)
	{
		return 1;
	}
	else if (X == (int32)720 && Y == (int32)480)
	{
		return 0;
	}

	return 3;
}

FText UOptionsGraphic::GetTextFromResolution(FIntPoint Resolution)
{
	FString X = FString::FromInt(Resolution.X);
	FString Y = FString::FromInt(Resolution.Y);
	FString Point = X + " x " + Y;

	return FText::FromString(Point);
}

void UOptionsGraphic::ChangeLevel(int32& OptionLevel, bool IsIncrease)
{
	if (IsIncrease == true) // 증가, Right Arrow가 클릭되었을 때
	{
		if (OptionLevel >= 3)
		{
			OptionLevel = 0;
		}
		else
		{
			OptionLevel = OptionLevel + 1;
		}
	}
	else // 감소, Left Arrow가 클릭되었을 때
	{
		if (OptionLevel <= 0)
		{
			OptionLevel = 3;
		}
		else
		{
			OptionLevel = OptionLevel - 1;
		}
	}
}

FText UOptionsGraphic::GetLevelTextFromInt(int32 num)
{
	FName LevelText{};
	switch (num)
	{
	case 0:
		LevelText = "Low";
		break;
	case 1:
		LevelText = "Medium";
		break;
	case 2:
		LevelText = "High";
		break;
	case 3:
		LevelText = "Epic";
		break;
	}
	return FText::FromName(LevelText);
}

void UOptionsGraphic::InitWindowMode()
{
	if (WindowModeOverlayButton)
	{
		WindowModeOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredWindowMode);
		WindowModeOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredWindowMode);
	}
	if (WindowModeButtonLeft)
	{
		WindowModeButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredWindowModeArrowLeft);
		WindowModeButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredWindowModeArrowLeft);
		WindowModeButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedWindowModeArrowLeft);
	}
	if (WindowModeButtonRight)
	{
		WindowModeButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredWindowModeArrowRight);
		WindowModeButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredWindowModeArrowRight);
		WindowModeButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedWindowModeArrowRight);
	}
	if (UserSettings && WindowModeSetText)
	{
		EWindowMode::Type WindowMode = UserSettings->GetFullscreenMode();

		WindowModeSetText->SetText(GetWindowModeText(WindowMode));

		Settings.WindowMode = WindowMode;
	}
}

void UOptionsGraphic::InitDisplayResolution()
{
	if (DisplayResolutionOverlayButton)
	{
		DisplayResolutionOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredDisplayResolution);
		DisplayResolutionOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredDisplayResolution);
	}
	if (DisplayResolutionButtonLeft)
	{
		DisplayResolutionButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredDisplayResolutionArrowLeft);
		DisplayResolutionButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredDisplayResolutionArrowLeft);
		DisplayResolutionButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedDisplayResolutionArrowLeft);
	}
	if (DisplayResolutionButtonRight)
	{
		DisplayResolutionButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredDisplayResolutionArrowRight);
		DisplayResolutionButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredDisplayResolutionArrowRight);
		DisplayResolutionButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedDisplayResolutionArrowRight);
	}

	if (UserSettings && DisplayResolutionSetText)
	{
		FIntPoint Resolution = UserSettings->GetScreenResolution();

		DisplayResolutionSetText->SetText(GetTextFromResolution(Resolution));

		Settings.ResolutionLevel = GetIntFromResolution(Resolution);
	}
}

void UOptionsGraphic::InitPostProcessing()
{
	if (PostProcessingOverlayButton)
	{
		PostProcessingOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredPostProcessing);
		PostProcessingOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredPostProcessing);
	}
	if (PostProcessingButtonLeft)
	{
		PostProcessingButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredPostProcessingArrowLeft);
		PostProcessingButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredPostProcessingArrowLeft);
		PostProcessingButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedPostProcessingArrowLeft);
	}
	if (PostProcessingButtonRight)
	{
		PostProcessingButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredPostProcessingArrowRight);
		PostProcessingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredPostProcessingArrowRight);
		PostProcessingButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedPostProcessingArrowRight);
	}
	if (UserSettings && PostProcessingSetText)
	{
		Settings.PostProcessingLevel = UserSettings->GetPostProcessingQuality();

		FText ShowingText = GetLevelTextFromInt(Settings.PostProcessingLevel);

		PostProcessingSetText->SetText(ShowingText);
	}
}

void UOptionsGraphic::InitAntiAliasing()
{
	if (AntiAliasingOverlayButton)
	{
		AntiAliasingOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredAntiAliasing);
		AntiAliasingOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredAntiAliasing);
	}
	if (AntiAliasingButtonLeft)
	{
		AntiAliasingButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredAntiAliasingArrowLeft);
		AntiAliasingButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredAntiAliasingArrowLeft);
		AntiAliasingButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedAntiAliasingArrowLeft);
	}
	if (AntiAliasingButtonRight)
	{
		AntiAliasingButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredAntiAliasingArrowRight);
		AntiAliasingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredAntiAliasingArrowRight);
		AntiAliasingButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedAntiAliasingArrowRight);
	}
	if (UserSettings && AntiAliasingSetText)
	{
		Settings.AntiAliasingLevel = UserSettings->GetAntiAliasingQuality();

		FText ShowingText = GetLevelTextFromInt(Settings.AntiAliasingLevel);

		AntiAliasingSetText->SetText(ShowingText);
	}
}

void UOptionsGraphic::InitTextureQuality()
{
	if (TextureQualityOverlayButton)
	{
		TextureQualityOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredTextureQuality);
		TextureQualityOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredTextureQuality);
	}
	if (TextureQualityButtonLeft)
	{
		TextureQualityButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredTextureQualityArrowLeft);
		TextureQualityButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredTextureQualityArrowLeft);
		TextureQualityButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedTextureQualityArrowLeft);
	}
	if (TextureQualityButtonRight)
	{
		TextureQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredTextureQualityArrowRight);
		TextureQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredTextureQualityArrowRight);
		TextureQualityButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedTextureQualityArrowRight);
	}
	if (UserSettings && TextureQualitySetText)
	{
		Settings.TextureQualityLevel = UserSettings->GetTextureQuality();

		FText ShowingText = GetLevelTextFromInt(Settings.TextureQualityLevel);

		TextureQualitySetText->SetText(ShowingText);
	}
}

void UOptionsGraphic::InitShadowQuality()
{
	if (ShadowQualityOverlayButton)
	{
		ShadowQualityOverlayButton->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredShadowQuality);
		ShadowQualityOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredShadowQuality);
	}
	if (ShadowQualityButtonLeft)
	{
		ShadowQualityButtonLeft->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredShadowQualityArrowLeft);
		ShadowQualityButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredShadowQualityArrowLeft);
		ShadowQualityButtonLeft->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedShadowQualityArrowLeft);
	}
	if (ShadowQualityButtonRight)
	{
		ShadowQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredShadowQualityArrowRight);
		ShadowQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredShadowQualityArrowRight);
		ShadowQualityButtonRight->OnClicked.AddDynamic(this, &UOptionsGraphic::OnClickedShadowQualityArrowRight);
	}
	if (UserSettings && ShadowQualitySetText)
	{
		Settings.ShadowQualityLevel = UserSettings->GetShadowQuality();

		FText ShowingText = GetLevelTextFromInt(Settings.ShadowQualityLevel);

		ShadowQualitySetText->SetText(ShowingText);
	}
}