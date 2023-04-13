// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/MainMenu.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitBack();
	InitWindowMode();
	InitDisplayResolution();
	InitPostProcessing();
	InitAntiAliasing();
	InitTextureQuality();
	InitShadowQuality();
	InitSound();
}

void UOptionsMenu::OnHoveredBackButton()
{
	if (ArrowLeft && ActivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(ActivatedArrowLeft);
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredBackButton()
{
	if (ArrowLeft && DeactivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivatedArrowLeft);
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnClickedBackButton()
{
	if (MainMenuClass)
	{
		UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(this, MainMenuClass));
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			RemoveFromParent();
		}
	}
}

void UOptionsMenu::OnHoveredWindowMode()
{
	if (WindowModeOverlayImage)
	{
		WindowModeOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredWindowMode()
{
	if (WindowModeOverlayImage)
	{
		WindowModeOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredWindowModeArrowLeft()
{
	if (WindowModeButtonLeftArrow && ActivatedArrowLeft)
	{
		WindowModeButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredWindowModeArrowLeft()
{
	if (WindowModeButtonLeftArrow && DeactivatedArrowLeft)
	{
		WindowModeButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredWindowModeArrowRight()
{
	if (WindowModeButtonRightArrow && ActivatedArrowRight)
	{
		WindowModeButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredWindowModeArrowRight()
{
	if (WindowModeButtonRightArrow && DeactivatedArrowRight)
	{
		WindowModeButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredDisplayResolution()
{
	if (DisplayResolutionOverlayImage)
	{
		DisplayResolutionOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredDisplayResolution()
{
	if (DisplayResolutionOverlayImage)
	{
		DisplayResolutionOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredDisplayResolutionArrowLeft()
{
	if (DisplayResolutionButtonLeftArrow && ActivatedArrowLeft)
	{
		DisplayResolutionButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredDisplayResolutionArrowLeft()
{
	if (DisplayResolutionButtonLeftArrow && DeactivatedArrowLeft)
	{
		DisplayResolutionButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredDisplayResolutionArrowRight()
{
	if (DisplayResolutionButtonRightArrow && ActivatedArrowRight)
	{
		DisplayResolutionButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredDisplayResolutionArrowRight()
{
	if (DisplayResolutionButtonRightArrow && DeactivatedArrowRight)
	{
		DisplayResolutionButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredPostProcessing()
{
	if (PostProcessingOverlayImage)
	{
		PostProcessingOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredPostProcessing()
{
	if (PostProcessingOverlayImage)
	{
		PostProcessingOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredPostProcessingArrowLeft()
{
	if (PostProcessingButtonLeftArrow && ActivatedArrowLeft)
	{
		PostProcessingButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredPostProcessingArrowLeft()
{
	if (PostProcessingButtonLeftArrow && DeactivatedArrowLeft)
	{
		PostProcessingButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredPostProcessingArrowRight()
{
	if (PostProcessingButtonRightArrow && ActivatedArrowRight)
	{
		PostProcessingButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredPostProcessingArrowRight()
{
	if (PostProcessingButtonRightArrow && DeactivatedArrowRight)
	{
		PostProcessingButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredAntiAliasing()
{
	if (AntiAliasingOverlayImage)
	{
		AntiAliasingOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredAntiAliasing()
{
	if (AntiAliasingOverlayImage)
	{
		AntiAliasingOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredAntiAliasingArrowLeft()
{
	if (AntiAliasingButtonLeftArrow && ActivatedArrowLeft)
	{
		AntiAliasingButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredAntiAliasingArrowLeft()
{
	if (AntiAliasingButtonLeftArrow && DeactivatedArrowLeft)
	{
		AntiAliasingButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredAntiAliasingArrowRight()
{
	if (AntiAliasingButtonRightArrow && ActivatedArrowRight)
	{
		AntiAliasingButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredAntiAliasingArrowRight()
{
	if (AntiAliasingButtonRightArrow && DeactivatedArrowRight)
	{
		AntiAliasingButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredTextureQuality()
{
	if (TextureQualityOverlayImage)
	{
		TextureQualityOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredTextureQuality()
{
	if (TextureQualityOverlayImage)
	{
		TextureQualityOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredTextureQualityArrowLeft()
{
	if (TextureQualityButtonLeftArrow && ActivatedArrowLeft)
	{
		TextureQualityButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredTextureQualityArrowLeft()
{
	if (TextureQualityButtonLeftArrow && DeactivatedArrowLeft)
	{
		TextureQualityButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredTextureQualityArrowRight()
{
	if (TextureQualityButtonRightArrow && ActivatedArrowRight)
	{
		TextureQualityButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredTextureQualityArrowRight()
{
	if (TextureQualityButtonRightArrow && DeactivatedArrowRight)
	{
		TextureQualityButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredShadowQuality()
{
	if (ShadowQualityOverlayImage)
	{
		ShadowQualityOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredShadowQuality()
{
	if (ShadowQualityOverlayImage)
	{
		ShadowQualityOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::OnHoveredShadowQualityArrowLeft()
{
	if (ShadowQualityButtonLeftArrow && ActivatedArrowLeft)
	{
		ShadowQualityButtonLeftArrow->SetBrushFromTexture(ActivatedArrowLeft);
	}
}

void UOptionsMenu::OnUnhoveredShadowQualityArrowLeft()
{
	if (ShadowQualityButtonLeftArrow && DeactivatedArrowLeft)
	{
		ShadowQualityButtonLeftArrow->SetBrushFromTexture(DeactivatedArrowLeft);
	}
}

void UOptionsMenu::OnHoveredShadowQualityArrowRight()
{
	if (ShadowQualityButtonRightArrow && ActivatedArrowRight)
	{
		ShadowQualityButtonRightArrow->SetBrushFromTexture(ActivatedArrowRight);
	}
}

void UOptionsMenu::OnUnhoveredShadowQualityArrowRight()
{
	if (ShadowQualityButtonRightArrow && DeactivatedArrowRight)
	{
		ShadowQualityButtonRightArrow->SetBrushFromTexture(DeactivatedArrowRight);
	}
}

void UOptionsMenu::OnHoveredSound()
{
	if (SoundOverlayImage)
	{
		SoundOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsMenu::OnUnhoveredSound()
{
	if (SoundOverlayImage)
	{
		SoundOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::InitBack()
{
	if (BackButton)
	{
		BackButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredBackButton);
		BackButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredBackButton);
		BackButton->OnClicked.AddDynamic(this, &UOptionsMenu::OnClickedBackButton);
	}

	if (ArrowLeft && DeactivatedArrowLeft)
	{
		ArrowLeft->SetBrushFromTexture(DeactivatedArrowLeft);
		ArrowLeft->SetDesiredSizeOverride(FVector2D(48.f));
	}

	if (ActiveBackButtonImage)
	{
		ActiveBackButtonImage->SetOpacity(0.f);
	}
}

void UOptionsMenu::InitWindowMode()
{
	if (WindowModeOverlayButton)
	{
		WindowModeOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredWindowMode);
		WindowModeOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredWindowMode);
	}
	if (WindowModeButtonLeft)
	{
		WindowModeButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredWindowModeArrowLeft);
		WindowModeButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredWindowModeArrowLeft);
	}
	if (WindowModeButtonRight)
	{
		WindowModeButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredWindowModeArrowRight);
		WindowModeButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredWindowModeArrowRight);
	}
}

void UOptionsMenu::InitDisplayResolution()
{
	if (DisplayResolutionOverlayButton)
	{
		DisplayResolutionOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredDisplayResolution);
		DisplayResolutionOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredDisplayResolution);
	}
	if (DisplayResolutionButtonLeft)
	{
		DisplayResolutionButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredDisplayResolutionArrowLeft);
		DisplayResolutionButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredDisplayResolutionArrowLeft);
	}
	if (DisplayResolutionButtonRight)
	{
		DisplayResolutionButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredDisplayResolutionArrowRight);
		DisplayResolutionButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredDisplayResolutionArrowRight);
	}
}

void UOptionsMenu::InitPostProcessing()
{
	if (PostProcessingOverlayButton)
	{
		PostProcessingOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredPostProcessing);
		PostProcessingOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredPostProcessing);
	}
	if (PostProcessingButtonLeft)
	{
		PostProcessingButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredPostProcessingArrowLeft);
		PostProcessingButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredPostProcessingArrowLeft);
	}
	if (PostProcessingButtonRight)
	{
		PostProcessingButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredPostProcessingArrowRight);
		PostProcessingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredPostProcessingArrowRight);
	}
}

void UOptionsMenu::InitAntiAliasing()
{
	if (AntiAliasingOverlayButton)
	{
		AntiAliasingOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredAntiAliasing);
		AntiAliasingOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredAntiAliasing);
	}
	if (AntiAliasingButtonLeft)
	{
		AntiAliasingButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredAntiAliasingArrowLeft);
		AntiAliasingButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredAntiAliasingArrowLeft);
	}
	if (AntiAliasingButtonRight)
	{
		AntiAliasingButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredAntiAliasingArrowRight);
		AntiAliasingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredAntiAliasingArrowRight);
	}
}

void UOptionsMenu::InitTextureQuality()
{
	if (TextureQualityOverlayButton)
	{
		TextureQualityOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredTextureQuality);
		TextureQualityOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredTextureQuality);
	}
	if (TextureQualityButtonLeft)
	{
		TextureQualityButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredTextureQualityArrowLeft);
		TextureQualityButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredTextureQualityArrowLeft);
	}
	if (TextureQualityButtonRight)
	{
		TextureQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredTextureQualityArrowRight);
		TextureQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredTextureQualityArrowRight);
	}
}

void UOptionsMenu::InitShadowQuality()
{
	if (ShadowQualityOverlayButton)
	{
		ShadowQualityOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredShadowQuality);
		ShadowQualityOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredShadowQuality);
	}
	if (ShadowQualityButtonLeft)
	{
		ShadowQualityButtonLeft->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredShadowQualityArrowLeft);
		ShadowQualityButtonLeft->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredShadowQualityArrowLeft);
	}
	if (ShadowQualityButtonRight)
	{
		ShadowQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredShadowQualityArrowRight);
		ShadowQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredShadowQualityArrowRight);
	}
}

void UOptionsMenu::InitSound()
{
	if (SoundOverlayButton)
	{
		SoundOverlayButton->OnHovered.AddDynamic(this, &UOptionsMenu::OnHoveredSound);
		SoundOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsMenu::OnUnhoveredSound);
	}
}