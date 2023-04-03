// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

UENUM(BlueprintType)
enum class EItemName : uint8
{
	EIN_None UMETA(DisplayName = "None"),
	EIN_HealthPotion UMETA(DisplayName = "HealthPotion"),
	EIN_StaminaPotion UMETA(DisplayName = "StaminaPotion"),
};

UENUM(BlueprintType)
enum class EItemEffect : uint8
{
	EIE_Health UMETA(DisplayName = "Health"),
	EIE_Stamina UMETA(DisplayName = "Stamina"),
};

USTRUCT(BlueprintType)
struct FPotionInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemEffect EffectType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 AmountMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Mesh;
};
