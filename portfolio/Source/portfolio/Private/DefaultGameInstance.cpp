// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"

FSoundSettings UDefaultGameInstance::GetSoundSettings() const
{
	return SoundSettings;
}

void UDefaultGameInstance::SetSoundSettings(ESoundOptionsType SoundType, float Value)
{
	switch (SoundType)
	{
	case ESoundOptionsType::ESOT_Master:
		SoundSettings.MasterVolume = Value;
		break;
	case ESoundOptionsType::ESOT_Effect:
		SoundSettings.EffectVolume = Value;
		break;
	case ESoundOptionsType::ESOT_Music:
		SoundSettings.MusicVolume = Value;
		break;
	}
}
