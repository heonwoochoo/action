// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingTypes.generated.h"

UENUM(BlueprintType)
enum class ESoundOptionsType : uint8
{
	ESOT_Master UMETA(DisplayName = "Master"),
	ESOT_Effect UMETA(DisplayName = "Effect"),
	ESOT_Music UMETA(DisplayName = "Music"),
};

USTRUCT(BlueprintType)
struct FSoundSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MasterVolume = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EffectVolume = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MusicVolume = 1.f;
};