

#include "HUD/Menu/OptionsGraphic.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/OptionsMenu.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsGraphic::NativeConstruct()
{
	Super::NativeConstruct();

	InitWindowMode();
	InitDisplayResolution();
	InitPostProcessing();
	InitAntiAliasing();
	InitTextureQuality();
	InitShadowQuality();
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
	}
	if (WindowModeButtonRight)
	{
		WindowModeButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredWindowModeArrowRight);
		WindowModeButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredWindowModeArrowRight);
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
	}
	if (DisplayResolutionButtonRight)
	{
		DisplayResolutionButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredDisplayResolutionArrowRight);
		DisplayResolutionButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredDisplayResolutionArrowRight);
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
	}
	if (PostProcessingButtonRight)
	{
		PostProcessingButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredPostProcessingArrowRight);
		PostProcessingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredPostProcessingArrowRight);
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
	}
	if (AntiAliasingButtonRight)
	{
		AntiAliasingButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredAntiAliasingArrowRight);
		AntiAliasingButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredAntiAliasingArrowRight);
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
	}
	if (TextureQualityButtonRight)
	{
		TextureQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredTextureQualityArrowRight);
		TextureQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredTextureQualityArrowRight);
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
	}
	if (ShadowQualityButtonRight)
	{
		ShadowQualityButtonRight->OnHovered.AddDynamic(this, &UOptionsGraphic::OnHoveredShadowQualityArrowRight);
		ShadowQualityButtonRight->OnUnhovered.AddDynamic(this, &UOptionsGraphic::OnUnhoveredShadowQualityArrowRight);
	}
}