﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/OptionsSound.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Components/ProgressBar.h"
#include "HUD/Menu/OptionsMenu.h"
#include "Kismet/GameplayStatics.h"

void UOptionsSound::NativeConstruct()
{
	Super::NativeConstruct();

	InitMaster();
	InitEffect();
	InitMusic();
}

void UOptionsSound::OnHoveredMaster()
{
	if (MasterOverlayImage)
	{
		MasterOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsSound::OnUnhoveredMaster()
{
	if (MasterOverlayImage)
	{
		MasterOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsSound::OnChangedMasterValue(float Value)
{
	if (MasterProgressBar && MasterMix && MasterClass)
	{
		MasterProgressBar->SetPercent(Value);
		SetVolume(MasterMix, MasterClass, Value);
	}
}

void UOptionsSound::OnHoveredEffect()
{
	if (EffectOverlayImage)
	{
		EffectOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsSound::OnUnhoveredEffect()
{
	if (EffectOverlayImage)
	{
		EffectOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsSound::OnChangedEffectValue(float Value)
{
	if (EffectProgressBar && EffectMix && EffectClass)
	{
		EffectProgressBar->SetPercent(Value);
		SetVolume(EffectMix, EffectClass, Value);
	}
}

void UOptionsSound::OnHoveredMusic()
{
	if (MusicOverlayImage)
	{
		MusicOverlayImage->SetOpacity(1.f);
	}
}

void UOptionsSound::OnUnhoveredMusic()
{
	if (MusicOverlayImage)
	{
		MusicOverlayImage->SetOpacity(0.f);
	}
}

void UOptionsSound::OnChangedMusicValue(float Value)
{
	if (MusicProgressBar && MusicMix && MusicClass)
	{
		MusicProgressBar->SetPercent(Value);
		SetVolume(MusicMix, MusicClass, Value);
	}
}

void UOptionsSound::InitMaster()
{
	if (MasterOverlayButton)
	{
		MasterOverlayButton->OnHovered.AddDynamic(this, &UOptionsSound::OnHoveredMaster);
		MasterOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsSound::OnUnhoveredMaster);
	}
	if (MasterSlider)
	{
		MasterSlider->OnValueChanged.AddDynamic(this, &UOptionsSound::OnChangedMasterValue);
	}
}

void UOptionsSound::InitEffect()
{
	if (EffectOverlayButton)
	{
		EffectOverlayButton->OnHovered.AddDynamic(this, &UOptionsSound::OnHoveredEffect);
		EffectOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsSound::OnUnhoveredEffect);
	}
	if (EffectSlider)
	{
		EffectSlider->OnValueChanged.AddDynamic(this, &UOptionsSound::OnChangedEffectValue);
	}

}

void UOptionsSound::InitMusic()
{
	if (MusicOverlayButton)
	{
		MusicOverlayButton->OnHovered.AddDynamic(this, &UOptionsSound::OnHoveredMusic);
		MusicOverlayButton->OnUnhovered.AddDynamic(this, &UOptionsSound::OnUnhoveredMusic);
	}
	if (MusicSlider)
	{
		MusicSlider->OnValueChanged.AddDynamic(this, &UOptionsSound::OnChangedMusicValue);
	}
}

void UOptionsSound::SetVolume(USoundMix* SoundMix, USoundClass* SoundClass, float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundClass, Value);
}