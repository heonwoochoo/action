// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DefaultGameInstance.generated.h"

UENUM(BlueprintType)
enum class ESoundOptionsType : uint8
{
	ESOT_Master UMETA(DisplayName = "Master"),
	ESOT_Effect UMETA(DisplayName = "Effect"),
	ESOT_Music UMETA(DisplayName = "Music"),
};

struct FSoundSettings
{
	float MasterVolume = 1.f;
	float EffectVolume = 1.f;
	float MusicVolume = 1.f;
};

UCLASS()
class PORTFOLIO_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	FSoundSettings SoundSettings;

public:
	FSoundSettings GetSoundSettings() const;
	void SetSoundSettings(ESoundOptionsType SoundType, float Value);
};
